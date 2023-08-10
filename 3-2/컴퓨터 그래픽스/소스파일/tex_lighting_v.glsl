#version 450

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

layout(location = 4) in vec3 VertexInitPos;
layout(location = 5) in vec3 VertexInitVel;
layout(location = 6) in float StartTime;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

out float Transp;

uniform float Time;

uniform vec3 Gravity;
uniform float ParticleLifetime;

uniform int isTexture;

void getEyeSpace(out vec3 norm, out vec3 position)
{
	position = vec3(v_matrix*m_matrix*vec4(vPosition, 1.0));
	norm = normalize(mat3(v_matrix*m_matrix)*vNormal);
}

void main()
{
	if(isTexture == 2){
		vec3 pos = vec3(0.0);
		Transp = 0.0;

		if (Time > StartTime) {
			float t = Time - StartTime;

			if (t < ParticleLifetime) {
				pos = VertexInitPos + VertexInitVel * t + Gravity * t * t;
				Transp = 1.0 - t / ParticleLifetime;
			}
		}
		gl_Position = proj_matrix * v_matrix*m_matrix*vec4(pos, 1.0);
	}
	else {
		getEyeSpace(Normal, Position);
		TexCoord = vTexCoord;

		gl_Position = proj_matrix * v_matrix*m_matrix*vec4(vPosition, 1.0);
	}
}