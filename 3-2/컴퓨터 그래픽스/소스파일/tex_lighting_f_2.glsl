#version 450
#extension GL_ARB_explicit_attrib_location : enable

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

in float Transp;
uniform sampler2D ParticleTex;

uniform sampler2D BrickTex;
uniform sampler2D MossTex;

uniform int isTexture;

struct LightInfo {
	vec4 Position;
	vec3 Intensity;
};
uniform LightInfo Light[3];

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform MaterialInfo Material;

out vec4 color;

vec3 phongModel(int i, vec4 P, vec3 N, out vec3 ambAndDiff, out vec3 spec)
{
	vec3 L;

	if (Light[i].Position.w == 0.0)
		L = normalize(Light[i].Position.xyz);
	else
		L = normalize((Light[i].Position - P).xyz);

	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L, N);
	float lDotN = max(dot(L, N), 0.0);

	vec3 ambient = Light[i].Intensity * Material.Ka;
	vec3 diffuse = Light[i].Intensity * Material.Kd * lDotN;
	ambAndDiff = ambient + diffuse;
	spec = vec3(0.0);

	if (lDotN > 0.0)
		spec = Light[i].Intensity * Material.Ks * pow(max(dot(R, V), 0.0), Material.Shininess);

	return ambient + diffuse + spec;
}

void main(void)
{
	vec3 ambAndDiff, spec; 
	vec4 bColor, mColor, texColor;
	
	vec3 LightIntensity = phongModel(0, vec4(Position, 1.0), Normal, ambAndDiff, spec);

	for (int i = 1; i < 3; i++)
		LightIntensity += phongModel(i, vec4(Position, 1.0), Normal, ambAndDiff, spec);

	LightIntensity = LightIntensity / 2;

	if (isTexture == 1) {
		bColor = texture(BrickTex, TexCoord);
		mColor = texture(MossTex, TexCoord);

		texColor = mix(bColor, mColor, mColor.a);

		color = vec4(ambAndDiff, 1.0)*texColor + vec4(spec, 1.0);
	}
	else if (isTexture == 2) {
		color = texture(ParticleTex, gl_PointCoord);
		color.a *= Transp;
	}
	else {
		color = vec4(ambAndDiff, 1.0) + vec4(spec, 1.0);
	}
}