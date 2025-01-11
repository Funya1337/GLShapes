#include "Mesh.h"
#include "Model.h"

#define WIDTH 2560
#define HEIGHT 1440

Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
  Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
  Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
  Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
  Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] =
{
  0, 1, 2,
  0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
  Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
  Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
  Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
  Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
  Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
  Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
  Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
  Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
  0, 1, 2,
  0, 2, 3,
  0, 4, 7,
  0, 7, 3,
  3, 7, 6,
  3, 6, 2,
  2, 6, 5,
  2, 5, 1,
  1, 5, 4,
  1, 4, 0,
  4, 5, 6,
  4, 6, 7
};

static void GLClearError()
{
  while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
  while (GLenum error = glGetError())
  {
    std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
  }
}

int main()
{
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
  if (window == NULL)
  {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  gladLoadGL();

  glViewport(0, 0, WIDTH, HEIGHT);

  Model backpack("models/backpack/backpack.obj");
  //Model human("models/human/human.obj");
  
  Texture textures[]
  {
    Texture("tile.jpg", "diffuse", 0),
    Texture("planksSpec.png", "specular", 1)
  };

  Shader shaderProgram("default.vert", "default.frag");
  std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
  std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
  std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
  Mesh floor(verts, ind, tex);

  Shader shaderProgramLight("light.vert", "light.frag");
  std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
  std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
  Mesh light(lightVerts, lightInd, tex);


  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
  glm::mat4 lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 pyramidModel = glm::mat4(1.0f);
  pyramidModel = glm::translate(pyramidModel, pyramidPos);

  shaderProgramLight.Activate();
  glUniformMatrix4fv(glGetUniformLocation(shaderProgramLight.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
  glUniform4f(glGetUniformLocation(shaderProgramLight.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  
  shaderProgram.Activate();
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CCW);

  Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

  double prevTime = 0.0;
  double crntTime = 0.0;
  double timeDiff;
  unsigned int counter = 0;
  int test = 0;

  // Activate vsync
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window))
  {
    crntTime = glfwGetTime();
    timeDiff = crntTime - prevTime;
    ++counter;
    if (timeDiff >= 1.0 / 30.0)
    {
      std::string FPS = std::to_string((1.0 / timeDiff) * counter);
      std::string ms = std::to_string((timeDiff / counter) * 1000);
      std::string newTitle = "OpenGL - " + FPS + "FPS / " + ms + "ms";
      glfwSetWindowTitle(window, newTitle.c_str());
      prevTime = crntTime;
      counter = 0;
    }

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.Input(window);
    camera.Inputs(window);
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    backpack.Draw(shaderProgram, camera);
    //floor.Draw(shaderProgram, camera);
    light.Draw(shaderProgramLight, camera);
    //human.Draw(shaderProgram, camera);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  shaderProgram.Delete();
  shaderProgramLight.Delete();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}