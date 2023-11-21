layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 vColor;

void main()
{
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    vColor = inColor;
}