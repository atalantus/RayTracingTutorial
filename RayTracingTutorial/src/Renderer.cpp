#include "Renderer.h"

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;

		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render()
{
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); ++y)
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); ++x)
		{
			glm::vec2 coord = {(float)x / m_FinalImage->GetWidth(), (float)y / m_FinalImage->GetHeight()};
			coord = coord * 2.0f - 1.0f;
			m_ImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coord);
		}


	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{
	glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
	glm::vec3 rayDir(coord.x, coord.y, -1.0f);
	float radius = 0.5f;
	rayDir = glm::normalize(rayDir);

	float a = glm::dot(rayDir, rayDir);
	float b = 2.0f * glm::dot(rayOrigin, rayDir);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	float sqrDiscr = b * b - 4.0f * a * c;

	if (sqrDiscr >= 0.0f)
	{
		float discr = sqrtf(sqrDiscr);
		float t1 = (-b + discr) / (2.0f * a);
		float t2 = (-b - discr) / (2.0f * a);

		float t = fminf(t1, t2);

		uint8_t brightness = (uint8_t)(powf(1.5f, 5.0f) / powf(t, 5.0f) * 255.0f);

		return 0xff000000 | (brightness << 8) | brightness;
	}

	return 0xffff0000;
}
