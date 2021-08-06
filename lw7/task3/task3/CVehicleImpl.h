#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>

template <typename Vehicle, typename Passenger>
class CVehicleImpl: public Vehicle
{
public:
	CVehicleImpl() = default;
	CVehicleImpl(size_t placeCount) : m_placeCount(placeCount) {};
	bool IsEmpty() const
	{
		return m_passengers.size() <= 0;
	}
	bool IsFull() const
	{
		return m_placeCount <= m_passengers.size();
	}
	size_t GetPlaceCount() const
	{
		return m_placeCount;
	}
	size_t GetPassengerCount() const
	{
		return m_passengers.size();
	}
	void RemoveAllPassengers()
	{
		m_passengers.clear();
	}
	void AddPassenger(std::shared_ptr<Passenger> pPassenger)
	{
		if (!IsFull())
		{
			m_passengers.push_back(pPassenger);
			return;
		}
		throw std::logic_error("vehicle is full");
	}
	Passenger const& GetPassenger(size_t index) const
	{
		if (0 <= index && index < m_passengers.size())
		{
			return *m_passengers[index];
		}
		throw std::out_of_range("index is out of range");
	}
	void RemovePassenger(size_t index)
	{
		if (0 <= index && index < m_passengers.size())
		{
			m_passengers.erase(m_passengers.begin() + index);
			return;
		}
		throw std::out_of_range("index is out of range");
	}
private:
	std::vector<std::shared_ptr<Passenger>> m_passengers = {};
	size_t m_placeCount = 0;
};

