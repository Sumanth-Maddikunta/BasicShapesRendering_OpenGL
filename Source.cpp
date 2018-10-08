#include<glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>
#include<glm.hpp>

#include "Shapes.h"

using namespace glm;
using namespace std;

const int SCR_WIDTH = 800, SCR_HEIGHT = 800;
enum  Shape_Type
{
	LINE,RECTANGLE,CIRCLE
};

Shape_Type current = CIRCLE;

Shape *C;
Shape *ShapeFactory();

const char *vertexShaderSource =
"#version 330 core\n "
"in vec2 aPos;\n "
"void main(){\n "
"gl_Position=vec4(aPos.x,aPos.y,1.0f,1.0f);}\0 ";

const char *fragmentShaderSource =
"#version 330 core\n "
"void main(){\n "
"gl_FragColor=vec4(1.0f,0.0f,0.0f,1.0f);}\0 ";

void processInput(GLFWwindow *window);
bool secondPoint=false;
bool firstClick=true;

vector<vec2> vertices;
int n = 0;
vec2 points[2];

const float anglediff = 10.0;
float radius = 0.5;


int main()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment_030", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW Init failed\n";
		glfwTerminate();
		exit(-1);
	}

	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);

	int  success;
	char infolog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, 0, infolog);
		cout << "VERTEXSHADER::COMPILATION::ERROR\n";
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, 0, infolog);
		cout << "FRAGMENTSHADER::COMPILATION::ERROR\n";
	}

	unsigned int shaderProg;
	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vertexShader);
	glAttachShader(shaderProg, fragmentShader);
	glLinkProgram(shaderProg);

	glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
	if (!success)
	{
		cout << "SHADERPROGRAM::COULDNT BE LINKED\n";

	}
	
	C = ShapeFactory();
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProg);
		//Input Function
		processInput(window);
		
		
		C->SetOriginPosition(points[1]);
		C->SetOtherPosition(points[0]);
		C->Draw();
		

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xpos, ypos;
		if (firstClick)
		{
			glfwGetCursorPos(window, &xpos, &ypos);
			cout << "Curser Position X-" << xpos << " Y-" << ypos << endl;
			firstClick = false;

			float x = (xpos - SCR_WIDTH / 2.0) / (SCR_WIDTH / 2.0);
			float y = -(ypos - SCR_HEIGHT / 2.0) / (SCR_HEIGHT / 2.0);

			vertices.push_back(vec2(x, y));

			cout << x << "\t" << y<<vertices.size()<<endl;
			if (secondPoint)
			{
				points[0] = vec2(x, y);
			}
			else
			{
				points[0] = vec2(x, y);
				points[1] = vec2(x, y);
			}
			secondPoint = !secondPoint;

		}
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		firstClick = true;
	}

}
Shape *ShapeFactory()
{
	if (current == LINE)
		return new Line();
	else if (current == RECTANGLE)
		return new Rectangle();
	else if (current == CIRCLE)
		return new Circle();
	else
		return new Line();

}