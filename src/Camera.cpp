#include "Camera.hpp"

#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

static Camera* s_camera;
static GLFWscrollfun s_oldCallback;

static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    s_camera->ProcessMouseScroll(yOffset);
    s_oldCallback(window, xOffset, yOffset);
}

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch,
    float zoom,
    float width,
    float height,
    float near,
    float far
):
    position{position}, worldUp{up}, yaw{yaw}, pitch{pitch}, zoom{zoom}, width{width}, height{height}, near{near},
    far{far}, movementSpeed{2.5f}, mouseSensitivity{0.1f}
{
    UpdateVectors();
    UpdateView();
    UpdateProj();
}

Camera::~Camera()
{
    Deinit();
}

void Camera::LookAt(glm::vec3 target)
{
    // Calculate the new front vector
    front = glm::normalize(target - position);
    // Also re-calculate the right and up vectors
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
    // Re-calculate Euler angles
    pitch = glm::degrees(glm::asin(front.y));
    yaw   = glm::mod(glm::degrees(glm::acos(front.x / glm::cos(glm::radians(pitch)))) * glm::sign(front.z), 360.0f);

    UpdateView();
}

void Camera::UpdateVectors()
{
    // Calculate the new front vector
    glm::vec3 newFront;
    newFront.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    newFront.y = glm::sin(glm::radians(pitch));
    newFront.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front      = glm::normalize(newFront);
    // Also re-calculate the right and up vectors
    right      = glm::normalize(glm::cross(front, worldUp));
    up         = glm::normalize(glm::cross(right, front));
}

glm::mat4& Camera::UpdateView()
{
    view = glm::lookAt(position, position + front, worldUp);
    return view;
}

glm::mat4& Camera::UpdateProj()
{
    proj = glm::perspective(glm::radians(zoom), width / height, near, far);
    return proj;
}

void Camera::ProcessTranslation(Camera::Movement direction, float deltaTime)
{
    if(direction == Movement::Forward)
        position += front * movementSpeed * deltaTime;
    if(direction == Movement::Backward)
        position -= front * movementSpeed * deltaTime;
    if(direction == Movement::Left)
        position -= right * movementSpeed * deltaTime;
    if(direction == Movement::Right)
        position += right * movementSpeed * deltaTime;
    if(direction == Movement::Up)
        position += up * movementSpeed * deltaTime;
    if(direction == Movement::Down)
        position -= up * movementSpeed * deltaTime;
    UpdateView();
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    yaw += xOffset * mouseSensitivity;
    pitch += yOffset * mouseSensitivity;

    if(constrainPitch)
        pitch = glm::clamp(pitch, -89.9f, +89.9f);

    UpdateVectors();
    UpdateView();
}

void Camera::ProcessMouseScroll(float yOffset)
{
    zoom = glm::clamp(zoom - yOffset, 1.0f, 45.0f);
    UpdateProj();
}

void Camera::InitForGLFW()
{
    s_camera      = this;
    s_oldCallback = glfwSetScrollCallback(Renderer::GetInstance().GetWindow(), ScrollCallback);
    m_initialized = true;
}

void Camera::Deinit()
{
    if(m_initialized)
    {
        glfwSetScrollCallback(Renderer::GetInstance().GetWindow(), s_oldCallback);
        m_initialized = false;
    }
}

void Camera::OnUpdate(float deltaTime)
{
    Renderer& r = Renderer::GetInstance();

    // Keyboard input
    GLFWwindow* window = r.GetWindow();
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ProcessTranslation(Camera::Movement::Forward, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ProcessTranslation(Camera::Movement::Backward, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ProcessTranslation(Camera::Movement::Left, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ProcessTranslation(Camera::Movement::Right, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        ProcessTranslation(Camera::Movement::Down, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        ProcessTranslation(Camera::Movement::Up, deltaTime);

    // Mouse movement
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);
    float deltaX = cursorX - m_cursorPos.x;
    float deltaY = m_cursorPos.y - cursorY; // Reversed since y-coordinates range from bottom to top
    m_cursorPos  = {cursorX, cursorY};
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        if(!m_mouseButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_mouseButtonPressed = true;
        }
        ProcessMouseMovement(deltaX, deltaY);
    }
    else if(m_mouseButtonPressed)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_mouseButtonPressed = false;
    }

    // Update camera projection dimensions
    auto [width, height] = r.GetViewportSize();
    this->width          = width;
    this->height         = height;
    UpdateProj();
}
