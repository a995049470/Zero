#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0 
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1

out vec3 ourPos; // 

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourPos = aPos; 
}