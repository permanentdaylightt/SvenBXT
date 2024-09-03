#ifdef OPENGL_UTILS_HPP_RECURSE_GUARD
#error Recursive header files inclusion detected in opengl_utils.hpp
#else //OPENGL_UTILS_HPP_RECURSE_GUARD

#define OPENGL_UTILS_HPP_RECURSE_GUARD

#ifndef OPENGL_UTILS_HPP_GUARD
#define OPENGL_UTILS_HPP_GUARD
#pragma once

#ifdef __cplusplus

class GLUtils
{
public:
	GLUtils();
	~GLUtils();

	void color(float r, float g, float b, float a) const;
	void color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
	void line_width(float width) const;
	void line(const Vector2D& start, const Vector2D& end) const;
	void circle(const Vector2D& center, const std::vector<Vector2D>& points) const;
	void rectangle(const Vector2D& corner_a, const Vector2D& corner_b) const;

	static std::vector<Vector2D> compute_circle(float radius);
};

#else //!__cplusplus
#error C++ compiler required to compile opengl_utils.hpp
#endif //__cplusplus

#endif //OPENGL_UTILS_HPP_GUARD

#undef OPENGL_UTILS_HPP_RECURSE_GUARD
#endif //OPENGL_UTILS_HPP_RECURSE_GUARD