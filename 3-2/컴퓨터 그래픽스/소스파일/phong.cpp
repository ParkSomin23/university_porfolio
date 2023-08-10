#include "cg-2.h"
#include "camera.h"
#include "vboplane.h"
#include "vboteapot.h"
#include "vbomesh.h"
#include "VBOTriangleBar.h"
#include "VBOCube.h"
#include "VBOSphere.h"
#include "bmpreader.h"
#include <vector>
#include <algorithm>

void startup();
void render();
void shutdown();
extern void version();

float m = 10.0;

float randFloat() {
	return ((float)rand() / RAND_MAX);
}

struct scene {
	int width = 750, height = 750;
	GLuint rendering_program;
	GLuint vertex_array_object;

	// 모델링 변수
	VBOPlane *plane;
	VBOPlane *p_plane;
	VBOCube *cube;
	VBOSphere *sphere;
	VBOMesh *gear;
	VBOMesh *tree;
	VBOMesh *cylinder;
	VBOMesh *cat;
	VBOMesh *building;
	VBOMesh *ivy;
	VBOMesh *curtain;

	// 뷰잉 변수
	mat4 model, view, proj, models;
	GLint m_loc, v_loc, proj_loc, color_loc;
	GLuint tex_object[4];
	float angle;

	float cam_x = 0.0, cam_y = 0.0;
	float move_x = 0.0;
	float move_y = 0.0;

	// gear rotate angle
	float r_angle = 0.0;
	float c_angle = 0.0;

	float sphere_move = 0.0;
	float move_rate = 3.5;

	vector <mat4> mvs;

	//particle
	GLuint initVel, startTime, particles, initPos;
	GLuint nParticles;
	float t, p_angle;
};
scene sc;

void generate_texture(GLubyte * data, int width, int height)
{
	int x, y;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			GLubyte c = (((x & 0x8) == 0) ^ ((y & 0x8) == 0))*255.0;
			data[(y * width + x) * 4 + 0] = c;
			data[(y * width + x) * 4 + 1] = c;
			data[(y * width + x) * 4 + 2] = c;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}
}
void initBuffers();

struct model {
	
};
model handle;

void startup()
{
	/******* OpenGL Initialization */
	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL); //Passes if the incoming depth value is less than or

	sc.t = 0.0;

	/**** Shaders as variables */
	sc.rendering_program = compile_shaders("tex_lighting_v.glsl", "tex_lighting_f_2.glsl"); //("perfrag.glsl", "perfragf.glsl");
	glUseProgram(sc.rendering_program);

	// modeling
	sc.plane = new VBOPlane(10.0f*m, 10.0f*m, 1, 1);
	sc.ivy = new VBOMesh("ivy.obj");
	sc.cat = new VBOMesh("cat4.obj");
	sc.gear = new VBOMesh("gear.obj");
	sc.cylinder = new VBOMesh("cylinder.obj");
	sc.cube = new VBOCube();
	sc.sphere = new VBOSphere();
	sc.curtain = new VBOMesh("Curtain.obj");

	// viewing
	sc.angle = 0.957283f;
	sc.model = mat4(1.0);

	//25
	sc.view = LookAt(vec3(25.0f, 150.0f, 180.0f), vec3(0.0f, 40.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	//sc.view = LookAt(vec3(0.0f, 180.0f, 180.0f), vec3(0.0f, 30.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	float cameraZ = sc.height * 0.5 / tan(radians(0.5*50.0));
	sc.proj = Perspective(50.0f, (float)sc.width / (float)sc.height, (float)0.001*cameraZ, (float)10.0*cameraZ);

	//ortho
	sc.m_loc = glGetUniformLocation(sc.rendering_program, "m_matrix");
	sc.v_loc = glGetUniformLocation(sc.rendering_program, "v_matrix");
	sc.proj_loc = glGetUniformLocation(sc.rendering_program, "proj_matrix");

	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(mat4(1.0)));
	glUniformMatrix4fv(sc.v_loc, 1, GL_FALSE, value_ptr(sc.view));
	glUniformMatrix4fv(sc.proj_loc, 1, GL_TRUE, value_ptr(sc.proj));

	// Lighting
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Light[0].Intensity"), 0.6, 0.6, 0.2);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Light[1].Intensity"), 0.2, 0.2, 0.6);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Light[2].Intensity"), 1.0, 1.0, 1.0);

	// Lighting Spot Light
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Spot.Intensity"), 0.9, 0.9, 0.9);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Spot.exponent"), 5.0f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Spot.cutoff"), 30.0f);			// angle

	//texture
	glActiveTexture(GL_TEXTURE0);
	sc.tex_object[0] = BMPReader::loadTex("brick1.bmp");
	glActiveTexture(GL_TEXTURE1);
	sc.tex_object[1] = BMPReader::loadTex("moss.bmp");
	glActiveTexture(GL_TEXTURE2);
	sc.tex_object[2] = BMPReader::loadTex("empty.bmp");

	glUniform1i(glGetUniformLocation(sc.rendering_program, "BrickTex"), 0);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "MossTex"), 1);


	// create the checkerboard pattern

	// Define some data to upload into the texture
	GLubyte* data = new GLubyte[64 * 64 * 4];
	generate_texture(data, 64, 64);

	glActiveTexture(GL_TEXTURE3);
	// Generate a name for the texture
	glGenTextures(1, &sc.tex_object[3]);
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, sc.tex_object[3]);

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexImage2D(GL_TEXTURE_2D, 0,
		GL_RGB,          // Offset 0, 0
		64, 64, 0,       // 64 x 64 texels, replace entire image
		GL_RGBA,
		GL_UNSIGNED_BYTE, 
		data);          // Pointer to data

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	delete[] data;


	//particle
	// modeling
	//sc.p_plane = new VBOPlane(13.0f, 10.0f, 200, 2);

	// Generate our vertex buffers
	initBuffers();
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Gravity"), 0.0, 3.0, 0.0);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "ParticleLifetime"), 200.0);

	// the particle texture
	glActiveTexture(GL_TEXTURE0);
	BMPReader::loadTex("p.bmp");
	glUniform1i(glGetUniformLocation(sc.rendering_program, "ParticleTex"), 0);
}

void initBuffers()
{
	sc.nParticles = 2000;

	// Generate the buffers 
	glGenBuffers(1, &sc.initVel);   // Initial velocity buffer 
	glGenBuffers(1, &sc.startTime); // Start time buffer 
	//
	glGenBuffers(1, &sc.initPos);

	// Allocate space for all buffers 
	int size = sc.nParticles * 3 * sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, sc.initVel);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, sc.startTime);
	glBufferData(GL_ARRAY_BUFFER, sc.nParticles * sizeof(float), NULL, GL_STATIC_DRAW);

	//
	glBindBuffer(GL_ARRAY_BUFFER, sc.initPos);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);

	// Fill the first velocity buffer with random velocities 
	vec3 v(0.0f);
	float velocity, theta, phi;  
	float pos; 
	vec3 p(0.0f);
	
	GLfloat *data = new GLfloat[sc.nParticles * 3];
	//
	GLfloat *data3 = new GLfloat[sc.nParticles * 3];

	for (unsigned int i = 0; i < sc.nParticles; i++) {
		theta = mix(0.0f, pi<float>() / 3.0f, randFloat());
		phi = mix(0.0f, (float)two_pi<float>(), randFloat());
		v.x = sinf(theta) * cosf(phi);
		v.y = cosf(theta);
		v.z = sinf(theta) * sinf(phi);
		//velocity = mix(10.0f, 50.0f, randFloat());
		velocity = mix(1.25f, 5.0f, randFloat());
		v = normalize(v) * velocity;

		data[3 * i] = v.x;
		data[3 * i + 1] = v.y;
		data[3 * i + 2] = v.z;

		//init pos
		pos = mix(-100.0f, 100.0f, randFloat());
		data3[3 * i] = pos;
		data3[3 * i + 1] = pos;
		data3[3 * i + 2] = pos;
	}
	glBindBuffer(GL_ARRAY_BUFFER, sc.initVel);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	delete[] data;

	glBindBuffer(GL_ARRAY_BUFFER, sc.initPos);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data3);
	delete[] data3;

	// Fill the start time buffer 
	float *data1 = new GLfloat[sc.nParticles];
	float time = 0.0f;
	float rate = 0.0075f;
	for (unsigned int i = 0; i < sc.nParticles; i++) {
		data1[i] = time;
		time += rate;
	}
	glBindBuffer(GL_ARRAY_BUFFER, sc.startTime);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sc.nParticles * sizeof(float), data1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] data1;

	// Attach these to the torus's vertex array 
	glGenVertexArrays(1, &sc.particles);
	glBindVertexArray(sc.particles);

	glBindBuffer(GL_ARRAY_BUFFER, sc.initVel);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, sc.startTime);
	glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(6);

	glBindBuffer(GL_ARRAY_BUFFER, sc.initPos);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(4);

}

void idle() {
	sc.angle += 0.01f;

	sc.r_angle -= 0.1f;
	sc.c_angle += 0.05f;

	//if (sc.sphere_move < 3.0 * m)
	//	sc.move_rate = 0.001f;

	//if (sc.sphere_move > 3.5 * m)
	//	sc.move_rate = -0.001f;

	sc.sphere_move += sc.move_rate;

	sc.view = LookAt(vec3(25.0f+5*cos(sc.move_x), 150.0f+5*sin(sc.move_y), 180.0f), vec3(0.0f, 40.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(sc.v_loc, 1, GL_FALSE, value_ptr(sc.view));

	sc.t += 0.002f;

	glutPostRedisplay();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glUseProgram(sc.rendering_program);

	//--particle------------------------------------------
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 2);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Time"), sc.t);
	glBindVertexArray(sc.particles);

	// Disable depth test
	glDisable(GL_DEPTH_TEST);
	// Enable Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable Point Size. Enable Point Coord.
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(60.0f);
	glEnable(GL_POINT_SPRITE);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

	glDrawArrays(GL_POINTS, 0, sc.nParticles);

	glEnable(GL_DEPTH_TEST);


	// Lighting
	glUniform4fv(glGetUniformLocation(sc.rendering_program, "Light[0].Position"), 1, value_ptr(sc.view*vec4(-50.0, 100.0, 0.0, 1.0f)));
	glUniform4fv(glGetUniformLocation(sc.rendering_program, "Light[1].Position"), 1, value_ptr(sc.view*vec4(50.0, 100.0f, 0.0f, 1.0f)));
	glUniform4fv(glGetUniformLocation(sc.rendering_program, "Light[2].Position"), 1, value_ptr(sc.view*vec4(30.0 * cos(sc.angle), 50.0f, 30.0 * sin(sc.angle), 1.0f)));

	// Spot Light
	vec4 lightPos = vec4(0.0f, 100.0f, 0.0f, 1.0f); //(15.0f * cos(sc.angle), 15.0f, 15.0f * sin(sc.angle), 1.0f);
	vec4 direction = sc.view * vec4(-lightPos);	// 바꿔져도 됨, sc.view주는 이유가 카메라 좌표 값 줘야해서
	glUniform4fv(glGetUniformLocation(sc.rendering_program, "Spot.Position"), 1, value_ptr(sc.view*lightPos));
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Spot.direction"), direction[0], direction[1], direction[2]);

	// --- gear --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.282f, 0.282f, 0.32f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.49f, 0.49f, 0.49f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.49f, 0.47f, 0.49f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 400.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);


	mat4 g1 = translate(mat4(1.0), vec3(1.0, 6.5, -4.0)*m);
	g1 = rotate(g1, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	g1 = rotate(g1, (float)radians(90.0), vec3(1.0, 0.0, 0.0));
	g1 = rotate(g1, (float)radians(sc.r_angle), vec3(0.0, 1.0, 0.0));
	g1 = scale(g1, vec3(0.9f, 1.0f, 0.9f)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(g1));
	sc.gear->render();

	mat4 g2 = translate(mat4(1.0), vec3(3.0, 8.0, -4.0)*m);
	g2 = rotate(g2, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	g2 = rotate(g2, (float)radians(90.0), vec3(1.0, 0.0, 0.0));
	g2 = rotate(g2, (float)radians(-1 * 2 * sc.r_angle), vec3(0.0, 1.0, 0.0));
	g2 = scale(g2, vec3(0.5f, 1.0f, 0.5f)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(g2));
	sc.gear->render();

	mat4 g3 = translate(mat4(1.0), vec3(-1.0, 4.5, -4.0)*m);
	g3 = rotate(g3, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	g3 = rotate(g3, (float)radians(90.0), vec3(1.0, 0.0, 0.0));
	g3 = rotate(g3, (float)radians(-1 * 1.9 * sc.r_angle), vec3(0.0, 1.0, 0.0));
	g3 = scale(g3, vec3(0.7f, 1.0f, 0.7f)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(g3));
	sc.gear->render();

	mat4 g4 = translate(mat4(1.0), vec3(-3.2, 8.5, -4.0)*m);
	g4 = rotate(g4, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	g4 = rotate(g4, (float)radians(90.0), vec3(1.0, 0.0, 0.0));
	g4 = rotate(g4, (float)radians(0.5 * sc.r_angle), vec3(0.0, 1.0, 0.0));
	g3 = scale(g4, vec3(0.6f, 1.0f, 0.6f)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(g3));
	sc.gear->render();

	mat4 g5 = translate(mat4(1.0), vec3(2.5, 4.5, -4.0)*m);
	g5 = rotate(g5, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	g5 = rotate(g5, (float)radians(90.0), vec3(1.0, 0.0, 0.0));
	g5 = rotate(g5, (float)radians(-3 * sc.r_angle), vec3(0.0, 1.0, 0.0));
	g5 = scale(g5, vec3(0.4f, 1.0f, 0.4f)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(g5));
	sc.gear->render();


	// --- cylinder --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.439, 0.1686, 0.439);   //정면 측면 같을 때
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.035, 0.8745, 0.9); //정면과 측면이 다른거
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 0.1f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 tb1 = translate(mat4(1.0), vec3(0.0, 0.0, 0.0));
	tb1 = scale(tb1, vec3(1.0, 1.0, 1.0)*m);
	tb1 = rotate(tb1, (float)radians(sc.c_angle), vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(tb1));
	sc.cylinder->render();


	// --- cat --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.8, 0.8, 0.8);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.1, 0.1, 0.1);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.12, 0.1355, 0.269); //0.1137, 0.1255, 0.259
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 10.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 c = translate(mat4(1.0), vec3(0.0, 0.6, 0.0)*m);
	c = rotate(c, (float)radians(sc.c_angle), vec3(0.0, 1.0, 0.0));
	c = scale(c, vec3(0.2, 0.2, 0.2)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(c));
	sc.cat->render();


	// --- cube --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.1f, 0.5f, 0.7f);   //정면 측면 같을 때
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.1f, 0.04f, 0.05f); //정면과 측면이 다른거
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 10.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 1);

	glUniform1i(glGetUniformLocation(sc.rendering_program, "BrickTex"), 3);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "MossTex"), 2);

	mat4 cu1 = translate(mat4(1.0), vec3(-3.8, 0.75, 3.5)*m);
	cu1 = rotate(cu1, (float)radians(30.0), vec3(0.0, 1.0, 0.0));
	cu1 = scale(cu1, vec3(1.5, 1.5, 1.5)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(cu1));
	sc.cube->render();

	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.282f, 0.282f, 0.32f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.49f, 0.49f, 0.49f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.49f, 0.47f, 0.49f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 100.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 cu2 = translate(mat4(1.0), vec3(-4.5, 0.2, 4.5)*m);
	cu2 = rotate(cu2, (float)radians(-18.0), vec3(0.0, 1.0, 0.0));
	cu2 = scale(cu2, vec3(0.4, 0.4, 0.4)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(cu2));
	sc.cube->render();


	// --- sphere --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.902f, 0.604, 0.757);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.941f, 0.941f, 0.369f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.8588f, 0.8588f, 0.8588f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 0.5f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 sp1 = translate(mat4(1.0), vec3(4.0, 0.75, 3.5)*m);
	sp1 = scale(sp1, vec3(0.009, 0.009, 0.009)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(sp1));
	sc.sphere->render();

	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.439, 0.1686, 0.439);   //정면 측면 같을 때
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.035, 0.8745, 0.9); //정면과 측면이 다른거
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 0.1f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 sp2 = translate(mat4(1.0), vec3(42.0 - 2 * cos(sc.move_x), 5.0, 45.0 + sin(sc.move_x)));
	sp2 = scale(sp2, vec3(0.005, 0.005, 0.005)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(sp2));
	sc.sphere->render();


	// --- ivy --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.3255, 0.6118, 0.337);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.627, 0.7, 0.431);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.11, 0.251, 0.0784);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 1.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 ivy2 = translate(mat4(1.0), vec3(5.1, 3.8, -2.0)*m);
	ivy2 = scale(ivy2, vec3(0.15, 0.15, 0.15)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(ivy2));
	sc.ivy->render();

	mat4 ivy3 = translate(mat4(1.0), vec3(5.2, 3.9, 2.5)*m);
	ivy3 = scale(ivy3, vec3(0.155, 0.155, 0.155)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(ivy3));
	sc.ivy->render();

	mat4 ivy4 = translate(mat4(1.0), vec3(5.6, 3.8, 2.5)*m);
	ivy4 = rotate(ivy4, (float)radians(190.0), vec3(0.0, 1.0, 0.0));
	ivy4 = scale(ivy4, vec3(0.155, 0.155, 0.155)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(ivy4));
	sc.ivy->render();


	//// --- handle --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.902f, 0.604, 0.757);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.941f, 0.941f, 0.369f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.8588f, 0.8588f, 0.8588f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 0.5f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);


	sc.models = translate(mat4(1.0f), vec3(50.0f, 50.0f, 10.0f));
	sc.models = rotate(sc.models, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	sc.models = rotate(sc.models, (float)radians(-sc.angle * 15), vec3(0, 1, 0));
	sc.mvs.push_back(sc.models);

	// base instance transformation
	sc.models = translate(sc.models, vec3(0, -2.5*m, 0));
	sc.models = scale(sc.models, vec3(0.05*m, 3 * m, 0.05*m));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(sc.models));
	glUniform3f(sc.color_loc, 0.3, 0.2, 0.9);
	sc.cylinder->render();	// base 그림

	sc.models = sc.mvs.back();	// 불러오기 base의 기준 축이 된다
	sc.mvs.pop_back();			// stack에서 지우기

	/***********************************************/
	sc.models = translate(sc.models, vec3(0.0, -1.2*m, 0.0));  // base에다가 transform
	sc.models = rotate(sc.models, (float)radians(90.0), vec3(0.0, 0.0, -1.0));
	sc.mvs.push_back(sc.models);

	// Lower Arm instance transformation
	sc.models = translate(sc.models, vec3(1.2*m, 0.0, 1.5));
	sc.models = scale(sc.models, vec3(0.05*m, 8 * m, 0.05*m));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(sc.models));
	sc.cylinder->render();

	sc.models = sc.mvs.back(); // 인스턴스 빼고 저장
	sc.mvs.pop_back();

	///***********************************************/
	sc.models = translate(sc.models, vec3(m, 4.5 * m, 0.0));
	sc.models = rotate(sc.models, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	sc.mvs.push_back(sc.models);

	sc.models = translate(sc.models, vec3(0.0, -8.0, 0.0));
	sc.models = rotate(sc.models, (float)radians(-sc.angle * 15), vec3(0, 1, 0));
	sc.models = scale(sc.models, vec3(0.5*m, 15, 0.5*m));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(sc.models));
	sc.cube->render();

	sc.models = sc.mvs.back();
	sc.mvs.pop_back();


	// --- cutain --------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.471f, 0.235f, 0.0471f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.941f, 0.941f, 0.369f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.9f, 0.9f, 0.9f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 10.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 cur = translate(mat4(1.0), vec3(-4.75, 0.7, 1.5)*m); //0.7
	cur = rotate(cur, (float)radians(87.0), vec3(0.0, 1.0, 0.0));
	cur = scale(cur, vec3(0.75, 0.75, 0.75)*m);
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(cur));
	sc.curtain->render();

	// --- box -----------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.9f, 0.9f, 0.9f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.7f, 0.7f, 0.7f);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.1f, 0.1f, 0.1f);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 180.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 1);

	glUniform1i(glGetUniformLocation(sc.rendering_program, "BrickTex"), 1);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "MossTex"), 3);

	mat4 back;
	back = translate(mat4(1.0), vec3(0.0, 5.0, -5.0)*m);
	back = rotate(back, (float)radians(90.0), vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(back));
	sc.plane->render();

	mat4 right;
	right = translate(mat4(1.0), vec3(5.0 + 0.25, 5.0, 0.0)*m);
	right = rotate(right, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	right = rotate(right, (float)radians(3.0), vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(right));
	sc.plane->render();

	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ka"), 0.839, 0.94, 1.0);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Kd"), 0.714, 0.8235, 0.87);
	glUniform3f(glGetUniformLocation(sc.rendering_program, "Material.Ks"), 0.6314, 0.345, 0.6314);
	glUniform1f(glGetUniformLocation(sc.rendering_program, "Material.Shininess"), 10.0f);
	glUniform1i(glGetUniformLocation(sc.rendering_program, "isTexture"), 0);

	mat4 left;
	left = translate(mat4(1.0), vec3(-5.0 - 0.25, 5.0, 0.0)*m);
	left = rotate(left, (float)radians(90.0), vec3(0.0, 0.0, 1.0));
	left = rotate(left, (float)radians(-3.0), vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(left));
	sc.plane->render();

	mat4 bottom;
	bottom = translate(mat4(1.0), vec3(0.0, 0.0, 0.0));
	bottom = scale(bottom, vec3(1.1, 1.0, 1.0));
	glUniformMatrix4fv(sc.m_loc, 1, GL_FALSE, value_ptr(bottom));
	sc.plane->render();

	glutSwapBuffers();
}

void shutdown()
{
	glDeleteProgram(sc.rendering_program);
}

void InputKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		sc.move_y += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		sc.move_y -= 0.1f;
		break;
	case GLUT_KEY_LEFT:
		sc.move_x -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		sc.move_x += 0.1f;
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(sc.width, sc.height);
	glutCreateWindow("20173994_박소민");
	glewInit();

	version();
	startup();
	glutDisplayFunc(render);
	glutIdleFunc(idle);

	glutSpecialFunc(InputKeyboard);

	glutMainLoop();
	shutdown();
	return 0;
}
