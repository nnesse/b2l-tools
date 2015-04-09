#version 330

in vec3 normal;
in vec2 uv;
in vec3 pos;
in vec4 tangent;

in ivec2 weights[6];

uniform mat4 mvp;
uniform mat4 groups[52];

out FS_IN {
	vec3 normal;
	vec2 uv;
	vec3 pos;
	vec4 tangent;
} vs_out;

uniform bool animated;
uniform float scale;

void main()
{
	vs_out.uv = uv;
	vec3 v;
	vec3 n;
	vec3 t;
	if (animated) {
		int i = 0;
		v = vec3(0);
		n = vec3(0);
		t = vec3(0);
		float total_weight = 0;
		for(i = 0; i < 4; i++) {
			float weight = (weights[i].y / (16535.0 * 0.5));
			total_weight += weight;
			int j = weights[i].x;
			if (j < 0)
				break;
			v += weight * (groups[j] * vec4(pos,1)).xyz;
			n += weight * (groups[j] * vec4(normal, 0)).xyz;
			t += weight * (groups[j] * vec4(tangent.xyz, 0)).xyz;
		}
		v /= total_weight;
		n /= total_weight;
	} else {
		v = pos;
		n = normal;
		t = tangent.xyz;
	}

	v = v * scale;
	vs_out.normal = n;
	vs_out.pos = v;
	vs_out.tangent = vec4(t, tangent.w);
	gl_Position = mvp * vec4(v, 1);
}
