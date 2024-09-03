#include "SvenBXT.h"

int CHudCrosshair::Init()
{
	m_iFlags |= HUD_ACTIVE;

	// OpenGL crosshair cvars
	bxt_cross = CVAR_CREATE("sbxt_cross", "0", 0);
	bxt_cross_color = CVAR_CREATE("sbxt_cross_color", "", 0);
	bxt_cross_alpha = CVAR_CREATE("sbxt_cross_alpha", "255", 0);
	bxt_cross_thickness = CVAR_CREATE("sbxt_cross_thickness", "2", 0);
	bxt_cross_size = CVAR_CREATE("sbxt_cross_size", "10", 0);
	bxt_cross_gap = CVAR_CREATE("sbxt_cross_gap", "3", 0);
	bxt_cross_outline = CVAR_CREATE("sbxt_cross_outline", "0", 0);
	bxt_cross_circle_radius = CVAR_CREATE("sbxt_cross_circle_radius", "0", 0);
	bxt_cross_dot_color = CVAR_CREATE("sbxt_cross_dot_color", "", 0);
	bxt_cross_dot_size = CVAR_CREATE("sbxt_cross_dot_size", "0", 0);
	bxt_cross_top_line = CVAR_CREATE("sbxt_cross_top_line", "1", 0);
	bxt_cross_bottom_line = CVAR_CREATE("sbxt_cross_bottom_line", "1", 0);
	bxt_cross_left_line = CVAR_CREATE("sbxt_cross_left_line", "1", 0);
	bxt_cross_right_line = CVAR_CREATE("sbxt_cross_right_line", "1", 0);

	return 0;
}

int CHudCrosshair::VidInit()
{
	return 1;
}

int CHudCrosshair::Draw(float time)
{
	if (!bxt_cross->value)
		return 0;

	float old_circle_radius = 0;
	std::vector<Vector2D> circle_points;

	float r = 0.0f, g = 0.0f, b = 0.0f;
	std::istringstream ss(bxt_cross_color->string);
	ss >> r >> g >> b;

	static float crosshairColor[3];
	crosshairColor[0] = r;
	crosshairColor[1] = g;
	crosshairColor[2] = b;

	float alpha = bxt_cross_alpha->value / 255.0f;

	Vector2D center(static_cast<float>(ScreenWidth) / 2.0f, static_cast<float>(ScreenHeight) / 2.0f);

	GLUtils gl;

	// Draw the outline.
	if (bxt_cross_outline->value > 0.0f)
	{
		gl.color(0.0f, 0.0f, 0.0f, alpha);
		gl.line_width(bxt_cross_outline->value);

		auto size = bxt_cross_size->value;
		auto gap = bxt_cross_gap->value;
		auto half_thickness = bxt_cross_thickness->value / 2.0f;
		auto half_width = bxt_cross_outline->value / 2.0f;
		auto offset = half_thickness + half_width;

		// Top line
		if (bxt_cross_top_line->value)
		{
			gl.line(Vector2D(center.x - offset, center.y - gap - size), Vector2D(center.x + offset, center.y - gap - size));
			gl.line(Vector2D(center.x + half_thickness, center.y - gap - size + half_width), Vector2D(center.x + half_thickness, center.y - gap - half_width));
			gl.line(Vector2D(center.x + offset, center.y - gap), Vector2D(center.x - offset, center.y - gap));
			gl.line(Vector2D(center.x - half_thickness, center.y - gap - half_width), Vector2D(center.x - half_thickness, center.y - gap - size + half_width));
		}

		// Bottom line
		if (bxt_cross_bottom_line->value)
		{
			gl.line(Vector2D(center.x - offset, center.y + gap + size), Vector2D(center.x + offset, center.y + gap + size));
			gl.line(Vector2D(center.x + half_thickness, center.y + gap + size - half_width), Vector2D(center.x + half_thickness, center.y + gap + half_width));
			gl.line(Vector2D(center.x + offset, center.y + gap), Vector2D(center.x - offset, center.y + gap));
			gl.line(Vector2D(center.x - half_thickness, center.y + gap + half_width), Vector2D(center.x - half_thickness, center.y + gap + size - half_width));
		}

		// Left line
		if (bxt_cross_left_line->value)
		{
			gl.line(Vector2D(center.x - gap - size, center.y - offset), Vector2D(center.x - gap - size, center.y + offset));
			gl.line(Vector2D(center.x - gap - size + half_width, center.y + half_thickness), Vector2D(center.x - gap - half_width, center.y + half_thickness));
			gl.line(Vector2D(center.x - gap, center.y + offset), Vector2D(center.x - gap, center.y - offset));
			gl.line(Vector2D(center.x - gap - half_width, center.y - half_thickness), Vector2D(center.x - gap - size + half_width, center.y - half_thickness));
		}

		// Right line
		if (bxt_cross_right_line->value)
		{
			gl.line(Vector2D(center.x + gap + size, center.y - offset), Vector2D(center.x + gap + size, center.y + offset));
			gl.line(Vector2D(center.x + gap + size - half_width, center.y + half_thickness), Vector2D(center.x + gap + half_width, center.y + half_thickness));
			gl.line(Vector2D(center.x + gap, center.y + offset), Vector2D(center.x + gap, center.y - offset));
			gl.line(Vector2D(center.x + gap + half_width, center.y - half_thickness), Vector2D(center.x + gap + size - half_width, center.y - half_thickness));
		}

		// Dot
		if (bxt_cross_dot_size->value > 0.0f)
		{
			auto size = bxt_cross_dot_size->value;
			auto offset = Vector2D(size / 2.0f, size / 2.0f);

			gl.line(Vector2D(center.x - offset.x - half_width, center.y - offset.y), Vector2D(center.x + offset.x + half_width, center.y - offset.y));
			gl.line(Vector2D(center.x + offset.x, center.y - offset.y + half_width), Vector2D(center.x + offset.x, center.y + offset.y - half_width));
			gl.line(Vector2D(center.x - offset.x, center.y - offset.y + half_width), Vector2D(center.x - offset.x, center.y + offset.y - half_width));
			gl.line(Vector2D(center.x - offset.x - half_width, center.y + offset.y), Vector2D(center.x + offset.x + half_width, center.y + offset.y));
		}
	}

	if (bxt_cross_color->string[0])
	{
		gl.color(crosshairColor[0], crosshairColor[1], crosshairColor[2], alpha);
	}
	else
	{
		gl.color(0.0f, 255.0f, 0.0f, alpha);
	}

	// Draw the crosshairs.
	if (bxt_cross_thickness->value > 0.0f)
	{
		gl.line_width(bxt_cross_thickness->value);

		auto size = bxt_cross_size->value;
		auto gap = bxt_cross_gap->value;

		if (bxt_cross_top_line->value)
			gl.line(Vector2D(center.x, center.y - gap - size), Vector2D(center.x, center.y - gap));
		if (bxt_cross_bottom_line->value)
			gl.line(Vector2D(center.x, center.y + gap + size), Vector2D(center.x, center.y + gap));
		if (bxt_cross_left_line->value)
			gl.line(Vector2D(center.x - gap - size, center.y), Vector2D(center.x - gap, center.y));
		if (bxt_cross_right_line->value)
			gl.line(Vector2D(center.x + gap + size, center.y), Vector2D(center.x + gap, center.y));
	}

	// Draw the circle.
	if (bxt_cross_circle_radius->value > 0.0f)
	{
		gl.line_width(1.0f);

		auto radius = bxt_cross_circle_radius->value;
		if (old_circle_radius != radius)
		{
			// Recompute the circle points.
			circle_points = gl.compute_circle(radius);
			old_circle_radius = radius;
		}

		gl.circle(center, circle_points);
	}

	// Draw the dot.
	if (bxt_cross_dot_size->value > 0.0f)
	{
		float r = 0.0f, g = 0.0f, b = 0.0f;
		std::istringstream ss(bxt_cross_dot_color->string);
		ss >> r >> g >> b;

		static float crosshairDotColor[2];
		crosshairDotColor[0] = r;
		crosshairDotColor[1] = g;
		crosshairDotColor[2] = b;

		if (bxt_cross_dot_color->string[0])
		{
			gl.color(crosshairDotColor[0], crosshairDotColor[1], crosshairDotColor[2], alpha);
		}
		else
		{
			gl.color(255.0f, 0.0f, 0.0f, alpha);
		}

		auto size = bxt_cross_dot_size->value;
		auto offset = Vector2D(size / 2.0f, size / 2.0f);

		gl.rectangle(center - offset, center + offset);
	}

	return 0;
}
