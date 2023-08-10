#version 450

in vec3 Position;
in vec3 Normal;

struct LightInfo {
	vec4 Position;
	vec3 Intensity;
};

uniform LightInfo Light[4];

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

uniform MaterialInfo Material;

out vec4 color;

vec3 phongModel(int i, vec4 P, vec3 N)
{
	vec3 L;

	if (Light[i].Position.w == 0.0)
		L = normalize(Light[i].Position.xyz);
	else 
		L = normalize((Light[i].Position - P).xyz);

	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L, N);

	float lDotN = max(dot(L, N), 0.0);
	vec3 ambient = Light[i].Intensity * Material.Ka / 3.0;
	vec3 diffuse = Light[i].Intensity * Material.Kd * lDotN;
	vec3 spec = vec3(0.0);

	if (lDotN > 0.0)
		spec = Light[i].Intensity * Material.Ks * pow(max(dot(R, V), 0.0), Material.Shininess);

	return ambient + diffuse + spec;

}

void main(void)
{
	vec3 LightIntensity = phongModel(0, vec4(Position, 1.0), Normal);
	for(int i =1; i<4;i++)
		LightIntensity += phongModel(i, vec4(Position, 1.0), Normal);

	LightIntensity = LightIntensity / 2;

	color = vec4(LightIntensity, 1.0);
}