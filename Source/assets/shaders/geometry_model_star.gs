#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

void build_star(vec4 position)
{   
	float scale = 0.5f;
    fColor = gs_in[0].color; // gs_in[0] since there's only one input vertex
    gl_Position = position + (vec4(-0.2f, 0.1f, 0.0f, 0.0f) * scale);    // 1:bottom-left   
    EmitVertex();   
    gl_Position = position + (vec4(0.2f, 0.1f, 0.0f, 0.0f) * scale);      // 2:bottom-right
    EmitVertex();
    gl_Position = position + (vec4(0.0f, -0.1f, 0.0f, 0.0f) * scale);    // 3:top-left
    EmitVertex();

	gl_Position = position + (vec4(-0.15f, -0.2f, 0.0f, 0.0f) * scale);    // 2:bottom-right
    EmitVertex();
	
	gl_Position = position + (vec4(  0.0f,  0.2f, 0.0f, 0.0f) * scale);    // 1:bottom-left   
    EmitVertex();   

    gl_Position = position + (vec4(  0.0f, -0.1f, 0.0f, 0.0f) * scale);    // 3:top-left
    EmitVertex();

	
	gl_Position = position + (vec4(  0.0f,  0.2f, 0.0f, 0.0f) * scale);    // 1:bottom-left   
    EmitVertex();   
    gl_Position = position + (vec4( 0.15f, -0.2f, 0.0f, 0.0f) * scale);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + (vec4( 0.0f, -0.1f, 0.0f, 0.0f) * scale);    // 3:top-left
    EmitVertex();



    EndPrimitive();

}

void main() {    
    build_star(gl_in[0].gl_Position);
}