#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		exit(1);
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	createProgram(vShaderCode, fShaderCode);
}

Shader::Shader(Shader& shader) {
	shaderProgram = shader.shaderProgram;
}

Shader::~Shader() {
}

void Shader::createProgram(const char* vertex_shader, const char* fragment_shader) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	checkShaderCompileError(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompileError(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	checkShaderCompileError(shaderProgram, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::deleteProgram() {
	glDeleteProgram(shaderProgram);
}

void Shader::use() {
	glUseProgram(shaderProgram);
}

void Shader::setUniform(const std::string& name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setUniform(const std::string& name, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void Shader::setUniform(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::update(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition) {
	use();
	setUniform("view", view);
	setUniform("projection", projection);
	setUniform("cameraPosition", cameraPosition);
}

void Shader::update(const glm::vec3& position, const glm::vec3& color) {
	use();
	setUniform("lightPos", position);
	setUniform("lightColor", color);
}

void Shader::update(float constant, float linear, float quadratic) {
	use();
	setUniform("constant", constant);
	setUniform("linear", linear);
	setUniform("quadratic", quadratic);
}

void Shader::update(const glm::vec3& cameraPos) {
	use();
	setUniform("viewPos", cameraPos);
}

void Shader::update(const glm::vec3& position, const glm::vec3& color, float constant, float linear, float quadratic, int i) {
	use();
	std::string lightIndex = "lights[" + std::to_string(i) + "]";
	setUniform(lightIndex + ".position", position);
	setUniform(lightIndex + ".color", color);
	setUniform(lightIndex + ".constant", constant);
	setUniform(lightIndex + ".linear", linear);
	setUniform(lightIndex + ".quadratic", quadratic);

}

void Shader::checkShaderCompileError(GLuint shader, const std::string& type) {
	GLint success;
	GLchar infoLog[1024];

	if (type == "PROGRAM") {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			exit(1);
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			exit(1);
		}
	}
}