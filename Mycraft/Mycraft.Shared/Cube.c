#include "Cube.h"

float _rotation;

static GLint vertices[][3] =
{
	{ -0x10000, -0x10000, -0x10000 },
	{ 0x10000, -0x10000, -0x10000 },
	{ 0x10000,  0x10000, -0x10000 },
	{ -0x10000,  0x10000, -0x10000 },
	{ -0x10000, -0x10000,  0x10000 },
	{ 0x10000, -0x10000,  0x10000 },
	{ 0x10000,  0x10000,  0x10000 },
	{ -0x10000,  0x10000,  0x10000 }
};

static GLint colors[][4] =
{
	{ 0x00000, 0x00000, 0x00000, 0x10000 },
	{ 0x10000, 0x00000, 0x00000, 0x10000 },
	{ 0x10000, 0x10000, 0x00000, 0x10000 },
	{ 0x00000, 0x10000, 0x00000, 0x10000 },
	{ 0x00000, 0x00000, 0x10000, 0x10000 },
	{ 0x10000, 0x00000, 0x10000, 0x10000 },
	{ 0x10000, 0x10000, 0x10000, 0x10000 },
	{ 0x00000, 0x10000, 0x10000, 0x10000 }
};

GLubyte indices[] =
{
	0, 4, 5,    0, 5, 1,
	1, 5, 6,    1, 6, 2,
	2, 6, 7,    2, 7, 3,
	3, 7, 4,    3, 4, 0,
	4, 7, 6,    4, 6, 5,
	3, 0, 1,    3, 1, 2
};

void Cube_setupGL(double width, double height)
{
	// Initialize GL state.
	glDisable(GL_DITHER);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glClearColor(1.0f, 0.41f, 0.71f, 1.0f);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);
	GLfloat ratio = (GLfloat)width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustumf(-ratio, ratio, -1, 1, 1, 10);
}

void Cube_tearDownGL()
{
}

void Cube_update()
{
	_rotation += 1.f;

}
void Cube_prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Cube_draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -3.0f);
	glRotatef(_rotation * 0.25f, 1, 0, 0);  // X
	glRotatef(_rotation, 0, 1, 0);          // Y

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glFrontFace(GL_CW);
	glVertexPointer(3, GL_FIXED, 0, vertices);
	glColorPointer(4, GL_FIXED, 0, colors);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
}


GLuint Cube_loadShaders(const char* vertex, const char* fragment) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int infoLogLen;

	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLen);
	
	if (infoLogLen > 0) {
		char* errorMessage = new char[infoLogLen + 1];
		glGetShaderInfoLog(vertexShader, infoLogLen, NULL, errorMessage);
		printf("%s\n", errorMessage);
	}

	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0) {
		char* errorMessage = new char[infoLogLen + 1];
		glGetShaderInfoLog(fragmentShader, infoLogLen, NULL, errorMessage);
		printf("%s\n", errorMessage);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);	

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
	if (infoLogLen > 0) {
		char* errorMessage = new char[infoLogLen + 1];
		glGetProgramInfoLog(program, infoLogLen, NULL, errorMessage);
		printf("%s\n", errorMessage);
	}

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}