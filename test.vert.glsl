#version 330

in vec3 vertex;
in vec3 normal;
in vec2 uv;
in vec4 tangent;

in ivec2 weights[6];

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 groups[52];

out FS_IN {
	vec3 normal;
	vec2 uv;
	vec3 pos;
	vec4 tangent;
} vs_out;

section Animation {
	uniform bool skinned;
};

void main()
{
	vs_out.uv = uv;
	vec3 v;
	vec3 n;
	vec3 t;
	int i = 0;
	v = vec3(0);
	n = vec3(0);
	t = vec3(0);
	if (skinned) {
		float total_weight = 0;
		for(i = 0; i < 6; i++) {
			float weight = (weights[i].y / (16535.0 * 0.5));
			total_weight += weight;
			int j = weights[i].x;
			if (j < 0)
				break;
			v += weight * (groups[j] * vec4(vertex,1)).xyz;
			n += weight * (groups[j] * vec4(normal, 0)).xyz;
			t += weight * (groups[j] * vec4(tangent.xyz, 0)).xyz;
		}
		v /= total_weight;
		n /= total_weight;
	} else {
		v = vertex;
		n = normal;
		t = tangent.xyz;
	}

	mat4 modelview = view * model;

	vs_out.normal = (modelview * vec4(n, 0)).xyz;
	vs_out.pos = (modelview * vec4(v, 0)).xyz;
	vs_out.tangent = vec4((modelview * vec4(tangent.xyz, 0)).xyz, tangent.w);
	gl_Position = proj * modelview * vec4(v, 1);
}
