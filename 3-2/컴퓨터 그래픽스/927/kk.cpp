#include "cg-2.h"
#include "time.h"

#define PI 3.14159265358979323846

void render();
void shutdown();

mat4 m[10];

struct scene {
	int width = 800, height = 300;
	GLuint rendering_program;
	GLuint vertex_array_object;

	vec4 vertices[200];
	vec4 colors[200];
	unsigned int indices[200];
	int num, numIndex;

	mat4 model;
	GLint mv_location;

	float theta;
	float x[16] = { 0 };
	float y[16] = { 0 };
	float r[16] = { 0 }; //scale
	float rotate_self[16] = { 0 };
};

//float sca = 0.001;
scene sc;

void pattern() {
	sc.num = 0;
	//Ã¢Æ²
	float a = 22.5 * PI / 180;
	for (int i = 0; i <= 21; i += 3) {
		sc.vertices[sc.num] = vec4(0.0, 0.0, 0.0, 1.0); sc.colors[sc.num++] = vec4(0.9f, 0.9f, 0.9f, 1.0f);
		sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.9f, 0.9f, 0.9f, 1.0f);
		a += (45 * PI / 180);
		sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.9f, 0.9f, 0.9f, 1.0f);
	}

	//°ËÁ¤
	float b_x = sc.vertices[2].x;
	float b_y = sc.vertices[1].y;

	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);
	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	sc.vertices[sc.num] = vec4(b_x, b_y, 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);

	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);
	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	sc.vertices[sc.num] = vec4(-b_x, b_y, 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);

	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);
	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	sc.vertices[sc.num] = vec4(-b_x, -b_y, 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);

	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	a += (45 * PI / 180);
	sc.vertices[sc.num] = vec4(0.4*float(cos(a)), 0.4*float(sin(a)), 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	sc.vertices[sc.num] = vec4(b_x, -b_y, 0, 1); sc.colors[sc.num++] = vec4(0.0f, 0.0f, 0.0f, 1.0f);


	//»ç¹æ»ö
	int count = sc.num;
	float w = 0.18;
	//Èò»ö
	float x = (sc.vertices[1].x + sc.vertices[2].x) / 2;
	float y = (sc.vertices[1].y + sc.vertices[2].y) / 2;
	float x_ = x - w;
	float y_ = y - w;
	cout << "sc" << sc.num << endl;
	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y - w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y - w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y - w, 0.0, 1.0);

	for (int i = count; i < count + 7; i++)
		sc.colors[i] = vec4(0.945f,0.9215f, 0.8471f, 1.0f);

	//»¡°­
	cout << "sc" << sc.num << endl;
	count = sc.num;
	sc.vertices[sc.num++] = vec4(-x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x, y - w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x + w, y - w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(-x_, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x_, y-w, 0.0, 1.0);

	for (int i = count; i < count + 7; i++)
		sc.colors[i] = vec4(0.84f, 0.353f, 0.2824f, 1.0f);

	//ÆÄ¶û
	count = sc.num;
	cout << "sc" << sc.num << endl;
	sc.vertices[sc.num++] = vec4(-x, -y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x + w, -y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x + w, -y + w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(-x + w, -y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x, -y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x, -y, 0.0, 1.0);

	for (int i = count; i < count + 7; i++)
		sc.colors[i] = vec4(0.275, 0.357, 0.6, 1.0f);

	//°Ë
	count = sc.num;
	cout << "sc" << sc.num << endl;
	sc.vertices[sc.num++] = vec4(x, -y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, -y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, -y + w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x - w, -y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, -y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, -y, 0.0, 1.0);

	for (int i = count; i < count + 7; i++)
		sc.colors[i] = vec4(0.0, 0.0, 0.0, 1.0f);

	//³ë¶û
	count = sc.num;
	x = 0.15;
	y = 0.15;
	sc.vertices[sc.num++] = vec4(x, -y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	cout << sc.num - 1 << endl;
	sc.vertices[sc.num++] = vec4(-x, y, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(-x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(-x, -y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, -y, 0.0, 1.0);

	for (int i = count; i < count + 7; i++)
		sc.colors[i] = vec4(0.957, 0.863f, 0.29, 1.0f);

	//Èò»öµé
	w = 0.1;
	count = sc.num;
	//w
	x = sc.vertices[36].x;
	y = sc.vertices[36].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x-w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x-w, y-w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y-w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y-w, 0.0, 1.0);

	//r
	x = sc.vertices[42].x;
	y = sc.vertices[42].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y - w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y - w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y - w, 0.0, 1.0);

	//bl
	x = sc.vertices[48].x;
	y = sc.vertices[48].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y + w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y + w, 0.0, 1.0);

	//b
	x = sc.vertices[54].x;
	y = sc.vertices[54].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y + w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y + w, 0.0, 1.0);


	//62 63 65 66
	w = 0.07;
	//r
	x = sc.vertices[62].x;
	y = sc.vertices[62].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y - w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y - w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y - w, 0.0, 1.0);

	//bla
	w = 0.065;
	x = sc.vertices[65].x;
	y = sc.vertices[65].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y + w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y + w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y + w, 0.0, 1.0);

	//bl
	x = sc.vertices[64].x;
	y = sc.vertices[64].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y + w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x + w, y+w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y + w, 0.0, 1.0);

	//w
	x = sc.vertices[61].x;
	y = sc.vertices[61].y;

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y - w, 0.0, 1.0);

	sc.vertices[sc.num++] = vec4(x, y, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x - w, y - w, 0.0, 1.0);
	sc.vertices[sc.num++] = vec4(x, y - w, 0.0, 1.0);


	for (int i = count; i < count + 56; i++)
		sc.colors[i] = vec4(1.0, 1.0, 1.0, 1.0f);
}

// ¸Ç Ã³À½ ÇÑ¹ø ½ÇÇà
void startup()
{
	sc.rendering_program = compile_shaders("vproject1.glsl", "fproject1.glsl");

	glGenVertexArrays(1, &sc.vertex_array_object);
	glBindVertexArray(sc.vertex_array_object);

	GLuint buffer[2];

	pattern();

	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sc.vertices), sc.vertices, GL_STATIC_DRAW);
	GLuint vPosition = glGetAttribLocation(sc.rendering_program, "vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vPosition);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sc.colors), sc.colors, GL_STATIC_DRAW);
	GLuint vColor = glGetAttribLocation(sc.rendering_program, "vColor");
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vColor);

	sc.model = mat4(1.0);
	sc.mv_location = glGetUniformLocation(sc.rendering_program, "mv_matrix");
	glUniformMatrix4fv(sc.mv_location, 1, GL_FALSE, value_ptr(sc.model));

	sc.theta = 0;
	float a = 0;
	for (int i = 0; i < 4; i++) {
		sc.x[i] = 0.2*cos(a);
		sc.y[i] = 0.2*sin(a);
		a += (90 * PI / 180);
		sc.rotate_self[i] = a;
	}

	for (int i = 0; i < 16; i++) {
		sc.r[i] = 0.35;
	}

	a = 90;
	for (int i = 4; i < 16; i++) {
		sc.rotate_self[i] = a;
		a += (55 * PI / 180);
	}

	int count = 4;
	float size = 0.65 / 3;

	//
	sc.x[count] = 3*size;
	sc.y[count++] = 0;

	sc.x[count] = 2 * size;
	sc.y[count++] = size;

	sc.x[count] = size;
	sc.y[count++] = 2 * size;

	sc.x[count] = 0;
	sc.y[count++] = 3* size;


	//
	sc.x[count] = -size;
	sc.y[count++] = 2* size;

	sc.x[count] = -2*size;
	sc.y[count++] = size;

	sc.x[count] = -3*size;
	sc.y[count++] = 0;


	//
	sc.x[count] = -2*size;
	sc.y[count++] = -size;

	sc.x[count] = -size;
	sc.y[count++] = -size*2;

	sc.x[count] = 0;
	sc.y[count++] = -size*3;


	//
	sc.x[count] = size;
	sc.y[count++] = -2*size;

	sc.x[count] = 2 * size;
	sc.y[count++] = -size;


	for (int i = 4; i < 16; i++) {
		sc.r[i] = 0.35;
	}

}

void idle()
{	
	static float a = 0;
	for (int i = 0; i < 4; i++) {
		sc.x[i] = 0.2 * cos(a);
		sc.y[i] = 0.2 * sin(a);
		a += (90 * PI / 180);
	}

	static float scale = 0.0005*2;
	for (int i = 0; i < 4; i++) {
		if (sc.r[i] > 0.35)
			scale = -0.0005*2;

		if (sc.r[i] < 0.0)
			scale = 0.0005*2;

		sc.r[i] += scale;
	}

	sc.theta = 0.0005*2;
	for (int i = 4; i < 16; i++) {
		sc.rotate_self[i] += sc.theta;
	}

	glutPostRedisplay();
}

void render()
{
	const GLfloat color[] = { 0.688, 174.0/255.0, 197.0/255.0, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(sc.rendering_program);

	for (int i = 0; i < 16; i++) {
		sc.model = translate(mat4(1.0), vec3(sc.x[i], sc.y[i], 0.0));
		sc.model = scale(sc.model, vec3(sc.r[i], sc.r[i], 0.0));

		sc.model = rotate(sc.model, sc.rotate_self[i], vec3(0.0, 0.0, 1.0));

		glUniformMatrix4fv(sc.mv_location, 1, GL_FALSE, value_ptr(sc.model));
		glDrawArrays(GL_TRIANGLES, 0, sc.num);
	}

	glutSwapBuffers();
}

void shutdown()
{
	glDeleteVertexArrays(1, &sc.vertex_array_object);
	glDeleteProgram(sc.rendering_program);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutCreateWindow("Korea");
	glewInit();
	version();

	startup();
	glutDisplayFunc(render);
	glutIdleFunc(idle);

	glutMainLoop();
	shutdown();
	return 0;
}
