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

    this->window = glfwCreateWindow(800, 600, "Hello World - GLEW and GLFW", nullptr, nullptr);
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
}

void Application::run() {
	Scene* scenes[3];
    scenes[0] = new SceneOne();
    scenes[1] = new SceneTwo();
	scenes[2] = new SceneThree();
    scenes[0]->init(window);
    scenes[1]->init(window);
	scenes[2]->init(window);

	int currentStage = 0;

    float lastFrame = glfwGetTime();
	
	// Z-buffer
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			scenes[currentStage]->deactivate();
			currentStage = 0;
			scenes[currentStage]->activate();
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            scenes[currentStage]->deactivate();
			currentStage = 1;
            scenes[currentStage]->activate();
        }
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			scenes[currentStage]->deactivate();
			currentStage = 2;
            scenes[currentStage]->activate();
		}
        
        scenes[currentStage]->handleInput(window);
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scenes[currentStage]->render();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}