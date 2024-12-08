#include "Application.h"
#include "SceneOne.h"
#include "SceneTwo.h"
#include "SceneThree.h"

Application::~Application() {
    // Clean up and close the application
    glfwDestroyWindow(window);
	glfwTerminate();
}

float Application::deltaTime = 0.0f;

float Application::getDeltaTime() {
	return deltaTime;
}

void Application::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(1000, 750, "Hello World - GLEW and GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(1);
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    glfwSetWindowUserPointer(window, this);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->mouseCallback(window, xPos, yPos);
	});
}

void Application::run() {
    scenes[0] = new SceneOne();
    scenes[1] = new SceneTwo();
	scenes[2] = new SceneThree();
    scenes[0]->init(window);
    scenes[1]->init(window);
	scenes[2]->init(window);

    float lastFrame = (float) glfwGetTime();
	scenes[0]->activate();
	
	// Z-buffer
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) {

		float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        
        processInput();

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scenes[activeScene]->render();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Application::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		scenes[activeScene]->deactivate();
		activeScene = 0;
		scenes[activeScene]->activate();
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		scenes[activeScene]->deactivate();
		activeScene = 1;
		scenes[activeScene]->activate();
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		scenes[activeScene]->deactivate();
		activeScene = 2;
		scenes[activeScene]->activate();
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		scenes[activeScene]->getController()->pressKey(window, GLFW_KEY_W);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		scenes[activeScene]->getController()->pressKey(window, GLFW_KEY_S);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		scenes[activeScene]->getController()->pressKey(window, GLFW_KEY_A);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		scenes[activeScene]->getController()->pressKey(window, GLFW_KEY_D);
	}
}

void Application::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	scenes[activeScene]->getController()->mouseCallback(window, xPos, yPos);
}