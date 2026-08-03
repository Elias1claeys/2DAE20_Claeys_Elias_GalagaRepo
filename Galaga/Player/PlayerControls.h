#include "Input/Command.h"

namespace dae
{
	class Player;

	class Move : public Command
	{
	protected:
		Player* m_Actor;

	public:
		void Execute(KeyState state) override;

		Move(Player* actor, glm::vec2 dir);
		virtual ~Move() = default;
		Move(const Move& other) = delete;
		Move(Move&& other) = delete;
		Move& operator=(const Move& other) = delete;
		Move& operator=(Move&& other) = delete;

	private:
		glm::vec2 m_Direction;
	};

	class Attack : public Command
	{
	protected:
		Player* m_Actor;

	public:
		void Execute(KeyState state) override;

		Attack(Player* actor);
		virtual ~Attack() = default;
		Attack(const Attack& other) = delete;
		Attack(Attack&& other) = delete;
		Attack& operator=(const Attack& other) = delete;
		Attack& operator=(Attack&& other) = delete;
	};
}