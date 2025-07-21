#pragma once

#include <glm/glm.hpp>

/**
 * @brief An abstract camera class that processes input and calculates the corresponding
 * Euler angles, vectors and matrices for use in OpenGL
 */
class Camera
{
public:
    /**
     * @brief Construct a new Camera object
     *
     * @param position Camera position
     * @param up World up vector
     * @param yaw Initial yaw \(in degrees\)
     * @param pitch Initial pitch \(in degrees\)
     * @param zoom Initial zoom \= projection FOV \(in degrees\)
     * @param width Initial projection width
     * @param height Initial projection height
     * @param near Initial near plane
     * @param far Initial far plane
     */
    Camera(
        glm::vec3 position,
        glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f},
        float yaw    = -90.0f,
        float pitch  = 0.0f,
        float zoom   = 45.0f,
        float width  = 800.0f,
        float height = 600.0f,
        float near   = 0.01f,
        float far    = 100.0f
    );
    /**
     * @brief Destroy the Camera object
     */
    ~Camera();

    /**
     * @brief Look at a point in space
     *
     * @param target
     */
    void LookAt(glm::vec3 target);

    /**
     * @brief Updates the camera's \c front, \c right and \c up vectors
     */
    void UpdateVectors();
    /**
     * @brief Update the camera's view matrix
     *
     * @return glm::mat4&
     */
    glm::mat4& UpdateView();
    /**
     * @brief Update the camera's projection matrix
     *
     * @return glm::mat4&
     */
    glm::mat4& UpdateProj();

    /**
     * @brief Enum to specify movement direction
     */
    enum class Movement : uint8_t
    {
        Forward  = 1 << 0,
        Backward = 1 << 1,
        Left     = 1 << 2,
        Right    = 1 << 3,
        Up       = 1 << 4,
        Down     = 1 << 5,
    };

    /**
     * @brief Moves the camera in the specified direction with set speed
     *
     * @param direction
     * @param deltaTime
     */
    void ProcessTranslation(Movement direction, float deltaTime);
    /**
     * @brief Rotates the camera with set sensitivity
     *
     * @param xOffset
     * @param yOfset
     * @param constrainPitch Constrain the pitch to the range of \f$ (-90.0f;+90.0f) \f$
     */
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    /**
     * @brief Zoom
     *
     * @param yOffset
     */
    void ProcessMouseScroll(float yOffset);

    /**
     * @brief Initializes the camera to be able to move according to input from GLFW
     */
    void InitForGLFW();
    /**
     * @brief Deinitialize the camera, uncoupling it from a GLFW window
     */
    void Deinit();
    /**
     * @brief To be called whenever the scene recieves an update
     *
     * @param deltaTime
     */
    void OnUpdate(float deltaTime);

public:
    // Camera attributes
    /**
     * @brief Camera view matrix
     */
    glm::mat4 view;
    /**
     * @brief Camera position
     */
    glm::vec3 position;
    /**
     * @brief Direction the camera is looking in
     */
    glm::vec3 front;
    /**
     * @brief Camera's relative up vector
     */
    glm::vec3 up;
    /**
     * @brief Camera's relative right vector
     */
    glm::vec3 right;
    /**
     * @brief World up vector
     */
    glm::vec3 worldUp;

    // Euler angles
    /**
     * @brief Camera's yaw \(in degrees\)
     */
    float yaw;
    /**
     * @brief Camera's pitch \(in degrees\)
     */
    float pitch;

    // Camera options
    /**
     * @brief Camera's movement speed
     */
    float movementSpeed;
    /**
     * @brief Mouse sensitivity for looking around
     */
    float mouseSensitivity;

    // Lens attributes
    /**
     * @brief Camera projection matrix
     */
    glm::mat4 proj;
    /**
     * @brief Camera's zoom \= projection's FOV
     */
    float zoom;
    /**
     * @brief Projection width
     */
    float width;
    /**
     * @brief Projection height
     */
    float height;
    /**
     * @brief Projection near plane
     */
    float near;
    /**
     * @brief Projection far plane
     */
    float far;

private:
    /**
     * @brief Whether this camera was initialized to work with GLFW
     */
    bool m_initialized = false;
    /**
     * @brief The cursor's position on the screen
     */
    glm::vec2 m_cursorPos;
    /**
     * @brief Is the left mouse button pressed
     */
    bool m_mouseButtonPressed = false;
};
