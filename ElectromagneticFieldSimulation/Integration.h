#pragma once

#include <cmath>
#include <algorithm>
#include <numbers>

namespace Math
{
	static class Integration
	{
	public:
		template <typename Function>
		static double GaussChebychev(Function function, double lowerLimit, double upperLimit);

	private:
		static const double MAX_BLOCK_SIZE;
		static const size_t MIN_POINTS_NUMBER;
		static const size_t MAX_POINTS_NUMBER;
	};

	template<typename Function>
	inline double Integration::GaussChebychev(Function function, double lowerLimit, double upperLimit)
	{
		size_t pointsNumber = std::clamp(static_cast<size_t>(std::floor((upperLimit - lowerLimit) / MAX_BLOCK_SIZE)), MIN_POINTS_NUMBER, MAX_POINTS_NUMBER);
		double distanceHalf = (upperLimit - lowerLimit) * 0.5;
		double limitSumHalf = (upperLimit + lowerLimit) * 0.5;
		
		double argumentCoeff = std::numbers::pi / (2.0 * pointsNumber);

		double result{};

		for (size_t pointIndex = 1; pointIndex <= pointsNumber; pointIndex++)
		{
			auto argumentX = std::cos((2.0 * pointIndex - 1.0) * argumentCoeff);
			auto argumentZ = distanceHalf * argumentX + limitSumHalf;

			result += function(argumentZ) * std::sqrt(1.0 - argumentX * argumentX);
		}

		result *= distanceHalf * std::numbers::pi / static_cast<double>(pointsNumber);

		return result;
	}
}
