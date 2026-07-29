#include "Texture.h"
#include "Transform.h"
#include "Resources/ResourceManager.h"

dae::Texture::Texture(GameObject* owner)
	: Component(owner)
{
	if (!owner->HasComponent<Transform>())
	{
		owner->AddComponent<Transform>();
	}
}

const void dae::Texture::Render()
{
	if (m_texture != nullptr)
	{
		auto pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		Renderer::GetInstance().Texture(*m_texture, pos, m_size, m_rotationAngle, m_FlipMode, m_srcRect.get());
	}
}

void dae::Texture::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_size = m_texture->GetSize();
}

void dae::Texture::SetTexture(SDL_Texture* texture)
{
	m_texture = std::make_shared<Texture2D>(texture);
	m_size = m_texture->GetSize();
}

void dae::Texture::FlipTexture()
{
	if (m_FlipMode == SDL_FLIP_NONE)
	{
		m_FlipMode = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		m_FlipMode = SDL_FLIP_NONE;
	}
}

void dae::Texture::SetSourceRect(float x, float y, float width, float height)
{
	if (m_srcRect == nullptr)
	{
		m_srcRect = std::make_unique<SDL_FRect>();
	}

	m_srcRect->x = x;
	m_srcRect->y = y;
	m_srcRect->w = width;
	m_srcRect->h = height;
}

glm::vec2 dae::Texture::GetSize()
{
	return m_size;
}