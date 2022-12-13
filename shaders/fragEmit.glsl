#version 330 core
out vec4 FragColor;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = vec4(.4f,0.4f,0.4f,1.0f);
}

