#pragma once
#include <vector>
#include <memory>
#include "Event.h"
#include "Event/Observer.h"

namespace dae
{

	class Subject
	{
	private:
		std::vector<std::unique_ptr<Observer>> m_Observers;

	public:
		void Notify(Event event, GameObject* gameObject);

		void AddObserver( std::unique_ptr<Observer> observer);
		void RemoveObserver(std::unique_ptr<Observer> observer);
	};
}
