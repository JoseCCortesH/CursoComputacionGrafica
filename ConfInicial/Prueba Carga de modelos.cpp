//p10

//Prueba carga de proyectos
//  Eduardo Zavala Sanchez
//	318105538
//

#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotChair = 180.0f; //Angulo de rotacion de sillas
float rotChair1 = 180.0f;
float rotChair2 = 180.0f;
float rotChair3 = 180.0f;
float rotChair4 = 180.0f;
float rotChair5 = 180.0f;
float rotChair6 = 180.0f;
float rotChair7 = 180.0f;
float rotChair8 = 180.0f;
float rotChair9 = 180.0f;
float rotChair10 = 180.0f;
float rotChair11 = 180.0f;
float rotChair12 = 180.0f;
float rotChair13 = 180.0f;
float rotChair14 = 180.0f;
float rotChair15 = 180.0f;
float rotChair16 = 180.0f;
float rotChair17 = 180.0f;
float rotChair18 = 180.0f;
float rotChair19 = 180.0f;
float rotChair1N = 180.0f;
float rotChair2N = 180.0f;
float rotChair3N = 180.0f;
float rotChair4N = 180.0f;
float rotChair5N = 180.0f;
float rotChair6N = 180.0f;
float rotChair7N = 180.0f;
float rotChair8N = 180.0f;
float rotChair9N = 180.0f;
float rotChair10N = 180.0f;
float rotChair11N = 180.0f;
float rotChair12N = 180.0f;
float rotChair13N = 180.0f;
float rotChair14N = 180.0f;
float rotChair15N = 180.0f;
float rotChair16N = 180.0f;
float rotChair17N = 180.0f;
float rotChair18N = 180.0f;
float rotChair19N = 180.0f;
float direccion = 1.0f;
float maxRot = 2.0f;
float radio = 1.0f;        // Radio del c rculo
float amplitud = 0.5f;     // Amplitud del movimiento senoidal
float frecuencia = 2.0f;   // Frecuencia del movimiento senoidal
float velocidad = 0.01f;
bool AnimBall = false;
bool AnimChairs = false;
bool AnimChairs2 = false;
bool AnimChairs3 = false;
bool AnimChairs4 = false;
bool AnimChairs5 = false;
bool AnimChairs6 = false;
bool AnimChairs7 = false;
float rotPantalla = 180.0f;
float angulo = 180.0f;
float rotTable = -270.0f;
float rotLib = -90.0f;
glm::vec3 chairPos1(3.4f, 0.01f, -2.4f);
glm::vec3 chairPos2(3.4f, 0.01f, -1.5f);
glm::vec3 chairPos3(3.4f, 0.01f, -0.5f);
glm::vec3 chairPos4(3.4f, 0.01f, 0.5);
glm::vec3 chairPos5(3.4f, 0.01f, 1.3f);
glm::vec3 chairPos6(3.4f, 0.01f, 2.3f);
glm::vec3 chairPos7(3.4f, 0.01f, 3.0f);
glm::vec3 chairPos8(1.0f, 0.01f, -2.5f);
glm::vec3 chairPos9(1.5f, 0.01f, -1.8f);
glm::vec3 chairPos10(1.5f, 0.01f, -0.8f);
glm::vec3 chairPos11(1.5f, 0.01f, -0.1f);
glm::vec3 chairPos12(1.5f, 0.01f, 0.5f);
glm::vec3 chairPos13(1.5f, 0.01f, 1.4f);
glm::vec3 chairPos14(1.5f, 0.01f, 2.3f);
glm::vec3 chairPos15(1.0f, 0.01f, 3.0f);
glm::vec3 chairPos16(-0.3f, 0.01f, 0.0f);
glm::vec3 chairPos17(-0.3f, 0.01f, 1.3f);
glm::vec3 chairPos18(-0.3f, 0.01f, 2.5f);
glm::vec3 chairPos19(-0.3f, 0.01f, 3.0f);
glm::vec3 chairPos1N(2.8f, 0.5f, -1.9f);
glm::vec3 chairPos2N(2.8f, 0.5f, -1.0f);
glm::vec3 chairPos3N(2.8f, 0.5f, 0.0f);
glm::vec3 chairPos4N(2.8f, 0.5f, 1.0f);
glm::vec3 chairPos5N(2.8f, 0.5f, 1.8f);
glm::vec3 chairPos6N(2.8f, 0.5f, 2.7f);
glm::vec3 chairPos7N(2.8f, 0.5f, 3.4f);
glm::vec3 chairPos8N(1.6f, 0.5f, -1.8f);
glm::vec3 chairPos9N(1.0f, 0.5f, -2.0f);
glm::vec3 chairPos10N(1.0f, 0.5f, -1.3f);
glm::vec3 chairPos11N(1.0f, 0.5f, -0.3f);
glm::vec3 chairPos12N(1.0f, 0.5f, 0.3f);
glm::vec3 chairPos13N(1.0f, 0.5f, 1.0f);
glm::vec3 chairPos14N(1.0f, 0.5f, 2.0);
glm::vec3 chairPos15N(0.5f, 0.01f, 0.0f);
glm::vec3 chairPos16N(-0.8f, 0.5f, 0.0f);
glm::vec3 chairPos17N(-0.8f, 0.5f, 1.0f);
glm::vec3 chairPos18N(-0.8f, 0.5f, 2.0f);
glm::vec3 chairPos19N(-0.8f, 0.5f, 2.7f);
glm::vec3 chairEsc(0.0001f, 0.0001f, 0.0001f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Eduardo Zavala Sanchez Prueba de Modelos y animacion ", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	//models
	Model Piso((char*)"Models/Piso.obj");
	//Model Gabeta((char*)"Models/Pantalla.obj");
	//Model Repisas((char*)"Models/Proyecto/Repisas.obj");
	//Model Servidor((char*)"Models/Proyecto/Servidor1.obj");
	//Model Lampara((char*)"Models/Proyecto/Lampara.obj");
	//Model Gabeta((char*)"Models/Proyecto/Gabeta.obj");
	Model Mesa((char*)"Models//Mesa.obj");
	Model Fila_Mesa1((char*)"Models/Fila_Mesas1.obj");
	Model Fila_Mesa2((char*)"Models/Fila_Mesas2.obj");
	Model Fila_Mesa3((char*)"Models/Fila_Mesas3.obj");
	Model Silla_A((char*)"Models/Silla_A.obj");
	Model Silla_Nueva_A((char*)"Models/Silla_Nueva_A.obj");
	Model Silla_Nueva_G((char*)"Models/Silla_Nueva_G.obj");
	Model Silla_Nueva_B((char*)"Models/Silla_Nueva_B.obj");
	Model Silla_Nueva_N((char*)"Models/Silla_Nueva_N.obj");
	Model Silla_B((char*)"Models/Silla_B.obj");
	Model Silla_N((char*)"Models/Silla_N.obj");
	Model Cuarto((char*)"Models/labprueba.obj");
	Model Techo((char*)"Models/techo.obj");
	Model Libreria((char*)"Models/Libreria.obj");
	Model Puerta((char*)"Models/Puerta.obj");
	Model Pantalla((char*)"Models/Pantalla.obj");
	Model PantallaInteligente((char*)"Models/Pantalla_Inteligente.obj");
	Model Pizarron((char*)"Models/Pizarron.obj");
	Model Lampara((char*)"Models/Lampara.obj");
	//=================================================================================================================================

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		angulo += deltaTime * 16.0f; //se puede multiplicar por una cantidad para aumentar la velocidad de rotacion
		if (angulo > 360) {
			angulo = 0.0f;
		}

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);






		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
		// =============================================
		// Primer foco 
		// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].position"), 0.0f, 5.0f, 0.0f);  // Posici�n original (centro del techo)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].outerCutOff"), glm::cos(glm::radians(15.0f)));

		// =============================================
		// Segundo foco (desplazado a la derecha)
		// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].position"), 3.0f, 5.0f, 0.0f);  // 3 unidades a la derecha en X
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[1].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[1].outerCutOff"), glm::cos(glm::radians(15.0f)));
	
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].position"), -2.5f, 5.0f, 0.0f);  // 3 unidades a la derecha en X
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[2].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[2].outerCutOff"), glm::cos(glm::radians(15.0f)));
		//	// =============================================
		// 
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[3].position"), -2.5f, 5.0f, 3.0f);  // 3 unidades a la derecha en X
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[3].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[3].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[3].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[3].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[3].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[3].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[3].outerCutOff"), glm::cos(glm::radians(15.0f)));
		//	// =============================================
		// 
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[4].position"), 3.0f, 5.0f, 3.0f);  // 3 unidades a la derecha en X
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[4].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[4].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[4].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[4].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[4].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[4].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[4].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[4].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[4].outerCutOff"), glm::cos(glm::radians(15.0f)));
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[5].position"), 0.0f, 5.0f, 2.4f);  // Posici�n original (centro del techo)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[5].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[5].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[5].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[5].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[5].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[5].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[5].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[5].cutOff"), glm::cos(glm::radians(8.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[5].outerCutOff"), glm::cos(glm::radians(15.0f)));
	// 
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[6].position"), -2.5f, 5.0f, -3.0f);  // 3 unidades a la derecha en X
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[6].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[6].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[6].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[6].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[6].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[6].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[6].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[6].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[6].outerCutOff"), glm::cos(glm::radians(15.0f)));
		//	// =============================================
		// 
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[7].position"), 3.0f, 5.0f, -3.0f);  // 3 unidades a la derecha en X
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[7].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[7].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[7].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[7].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[7].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[7].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[7].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[7].cutOff"), glm::cos(glm::radians(10.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[7].outerCutOff"), glm::cos(glm::radians(15.0f)));
		//	// =============================================
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[8].position"), 0.0f, 5.0f,-2.4f);  // Posici�n original (centro del techo)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[8].direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[8].ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[8].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[8].specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[8].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[8].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[8].quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[8].cutOff"), glm::cos(glm::radians(8.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[8].outerCutOff"), glm::cos(glm::radians(15.0f)));
		// 
	//// Foco tipo spotlight desde arriba (NUEVO)
	//// =============================================
	//	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 0.0f, 5.0f, 0.0f);  // Posici�n en el techo
	//	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f, -1.0f, 0.0f); // Direcci�n hacia abajo
	//	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.2f);
	//	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
	//	glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.5f, 0.5f, 0.5f);
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));  // �ngulo estrecho
	//	glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
	//	// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);
		glm::mat4 modelTemp(1);


		//================================================================================================================
		//Carga de modelo 
		//================================================================================================================
		view = camera.GetViewMatrix();
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuarto.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.0f,0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Techo.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.597f, 0.0f, -0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta.Draw(lightingShader);
		//==================================Carga de modelos Primera Fila=======================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(2.5f, 0.0f, 0.3f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fila_Mesa1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos7);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair7), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos6);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair6), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos5);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair5), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos4);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair4), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos3);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos2);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos1);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos1N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair7N+90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos2N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair6N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos3N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair5N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos4N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair4N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos5N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair3N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos6N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair2N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos7N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair1N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);
		//==================================Carga de modelos Segunda Fila=======================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.3f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fila_Mesa2.Draw(lightingShader);
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos15);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair15-50), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos14);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair14-25), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos13);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair13 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos12);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair12 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos11);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair11), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos10);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair10 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos9);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair9 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos8);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair8+60), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos8N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair8N+180), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos9N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair9N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos10N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair10N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos11N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair11N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos12N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair12N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos13N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair13N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos14N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair14N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);
		//==================================Carga de modelos Tercera Fila=======================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.2f, 0.0f, 2.6f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fila_Mesa3.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos19);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair19), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos18);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair18), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos17);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair17), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos16);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair16), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos16N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair16N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos17N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair17N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos18N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair18N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos19N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair19N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_N.Draw(lightingShader);
		//======================================================================================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(4.1f, 0.02f, 2.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		model = glm::rotate(model, glm::radians(rotLib), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Libreria.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.7f, 3.4f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(rotPantalla), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pantalla.Draw(lightingShader);
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-1.3f, 0.7f, -2.5f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(rotPantalla-90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pantalla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-2.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(rotPantalla - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PantallaInteligente.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotPantalla +90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.0f, 0.2f, 2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotPantalla + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(3.0f, 0.2f, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotPantalla - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.0f, 0.2f, 2.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(rotTable - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0005f, 0.0005f, 0.0005f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.Draw(lightingShader);

		
		//================================================================================================================
		// 
		//================================================================================================================
		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)

		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);

		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	if (keys[GLFW_KEY_N])
	{
		AnimChairs = !AnimChairs;

	}
}
//GLuint modelLoc = glGetUniformLocation(lampShader.Program, "model");
void Animation() {

	if (AnimChairs) {
		if (chairPos1.z >= -3.8) {
			chairPos1.z -= 0.01;
			AnimChairs2 = !AnimChairs2;
		}
		if (chairPos2.z >= -3.8) {
			chairPos2.z -= 0.01;
		}
		if (chairPos3.z >= -3.8) {
			chairPos3.z -= 0.01;
		}
		if (chairPos4.z >= -3.8) {
			chairPos4.z -= 0.01;
		}
		if (chairPos5.z >= -3.8) {
			chairPos5.z -= 0.01;
		}
		if (chairPos6.z >= -3.8) {
			chairPos6.z -= 0.01;
		}
		if (chairPos7.z >= -3.8) {
			chairPos7.z -= 0.01;
		}

	}
	
	if (AnimChairs2) {
		if (chairPos1.z <= -3.8) {
			rotChair1 += 1.01;
			chairPos1.x += 0.01;
		}
		if (chairPos2.z <= -3.8) {
			rotChair2 += 1.01;
			chairPos2.x += 0.01;
		}
		if (chairPos3.z <= -3.8) {
			rotChair3 += 1.01;
			chairPos3.x += 0.01;
		}
		if (chairPos4.z <= -3.8) {
			rotChair4 += 1.01;
			chairPos4.x += 0.01;
		}
		if (chairPos5.z <= -3.8) {
			rotChair5 += 1.01;
			chairPos5.x += 0.01;
		}
		if (chairPos6.z <= -3.8) {
			rotChair6 += 1.01;
			chairPos6.x += 0.01;
		}
		if (chairPos7.z <= -3.8) {
			rotChair7 += 1.01;
			chairPos7.x += 0.01;
		}
		if (chairPos7.x >= 4.0) {
			AnimChairs3 = !AnimChairs3;
		}
		
	}
	if (AnimChairs3) {
		if (chairPos8.z >= -3.8) {
			chairPos8.z -= 0.01;
			AnimChairs4 = !AnimChairs4;
		}
		if (chairPos9.z >= -3.8) {
			chairPos9.z -= 0.01;
		}
		if (chairPos10.z >= -3.8) {
			chairPos10.z -= 0.01;
		}
		if (chairPos11.z >= -3.8) {
			chairPos11.z -= 0.01;
		}
		if (chairPos12.z >= -3.8) {
			chairPos12.z -= 0.01;
		}
		if (chairPos13.z >= -3.8) {
			chairPos13.z -= 0.01;
		}
		if (chairPos14.z >= -3.8) {
			chairPos14.z -= 0.01;
		}
		if (chairPos15.z >= -3.8) {
			chairPos15.z -= 0.01;
		}
	}
	if (AnimChairs4) {
		if (chairPos8.z <= -3.8) {
			rotChair8 += 1.01;
			chairPos8.x += 0.01;
		}
		if (chairPos9.z <= -3.8) {
			rotChair9 += 1.01;
			chairPos9.x += 0.01;
		}
		if (chairPos10.z <= -3.8) {
			rotChair10 += 1.01;
			chairPos10.x += 0.01;
		}
		if (chairPos11.z <= -3.8) {
			rotChair11 += 1.01;
			chairPos11.x += 0.01;
		}
		if (chairPos12.z <= -3.8) {
			rotChair12 += 1.01;
			chairPos12.x += 0.01;
		}
		if (chairPos13.z <= -3.8) {
			rotChair13 += 1.01;
			chairPos13.x += 0.01;
		}
		if (chairPos14.z <= -3.8) {
			rotChair14 += 1.01;
			chairPos14.x += 0.01;
		}
		if (chairPos15.z <= -3.8) {
			rotChair15 += 1.01;
			chairPos15.x += 0.01;
		}
		if (chairPos15.x >= 4.0) {
			AnimChairs5 = !AnimChairs5;
		}
		

	}
	if (AnimChairs5) {
		if (chairPos16.z >= -3.8) {
			chairPos16.z -= 0.01;
			AnimChairs6 = !AnimChairs6;
		}
		if (chairPos17.z >= -3.8) {
			chairPos17.z -= 0.01;
		}
		if (chairPos18.z >= -3.8) {
			chairPos18.z -= 0.01;
		}
		if (chairPos19.z >= -3.8) {
			chairPos19.z -= 0.01;
		}
	}
	if (AnimChairs6) {
		if (chairPos16.z <= -3.8) {
			rotChair16 += 1.01;
			chairPos16.x += 0.01;
		}
		if (chairPos17.z <= -3.8) {
			rotChair17 += 1.01;
			chairPos17.x += 0.01;
		}
		if (chairPos18.z <= -3.8) {
			rotChair18 += 1.01;
			chairPos18.x += 0.01;
		}
		if (chairPos19.z <= -3.8) {
			rotChair19 += 1.01;
			chairPos19.x += 0.01;
		}
		if (chairPos19.x >= 4.0) {
			AnimChairs7 = !AnimChairs7;
		}
	}
	if (AnimChairs7) {
		if (chairEsc.z <=1.1) {
			chairEsc.z += 0.01;
		}
		if (chairEsc.y <= 1.1) {
			chairEsc.y += 0.01;
		}
		if (chairEsc.x <= 1.1) {
			chairEsc.x += 0.01;
		}
	}


	}




void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}