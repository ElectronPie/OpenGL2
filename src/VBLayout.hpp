#pragma once

#include <vector>

struct VBElement
{
    static unsigned int GetTypeSize(unsigned int type) noexcept;

    unsigned int type;
    unsigned int count;
    unsigned int normalized;
};

/**
 * @brief Represents the memory layout of an OpenGL vertex buffer
 *
 */
class VBLayout
{
public:
    /**
     * @brief Construct a new VBLayout object
     *
     */
    VBLayout();
    /**
     * @brief Destroy the VBLayout object
     *
     */
    ~VBLayout();

    /**
     * @brief Get the elements of the layout as a std::vector
     *
     * @return const std::vector<VBElement>&
     */
    inline const std::vector<VBElement>& GetElements() const noexcept
    {
        return m_elements;
    }

    /**
     * @brief Get the stride of the layout
     *
     * @return unsigned int
     */
    inline unsigned int GetStride() const noexcept
    {
        return m_stride;
    }

    /**
     * @brief Add an element of \a count values of type \a T to the layout
     *
     * @tparam T Type of appended values
     * @param count Amount of values
     */
    template<typename T>
    void Push(unsigned int count);

private:
    /**
     * @brief Elements of the layout
     *
     */
    std::vector<VBElement> m_elements;
    /**
     * @brief Layout's stride
     *
     */
    unsigned int m_stride = 0;
};
