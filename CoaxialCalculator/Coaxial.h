#pragma once
#include <cmath>
#include <corecrt_math_defines.h>
#include <string>
#include <cassert>

namespace Coaxial {
	//�������� ����� � �������, �/�
	constexpr double lightSpeed = 299792458.0;

	//������������� ����������
	constexpr double electricalConstant = 8.85418781762039e-12;

	//��������� ����������
	constexpr double magneticConstant = 1.2566370621219e-6;

	//����������: ����������� ��������� ������������� ������ ������ 1,
	//��� ��� ��������� � ������ ������������ �� ����� �������� ��� ������������ ������������ ����� �� ������������ (��� ��� �������������)

	//����� ���������� � ���������� �������� ��� ������ ����������� �������� (wchar_t - 2-�������� ������)
	class exception final {
		//������ � ��������� ��������
		std::wstring description_;
	public:
		//�����������
		//description - rvalue-������ �� ������ � �������� ����������
		exception(std::wstring&& description) :description_(std::move(description)) {}
		//����������
		~exception() {}

		//����� ������ ��������� � ����������� (� ����� C-������)
		wchar_t const* what()const noexcept {
			return description_.c_str();
		}
	};

	//������������ ����� ����� � ������������ ����� (� ������)
	//frequency - ������� ������������� �������, ��
	//epsilon - ��������������� ������������� �����������
	double wavelengthInTheLine(double const frequency, double const epsilon) {
		if (frequency <= 0.0)
			throw exception(L"������� ������ ���� ������ 0");
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");

		//����� ����� � �������
		double const lambda_0 = lightSpeed / frequency;
		double const lambda = lambda_0 / sqrt(epsilon);
		return lambda;
	}

	//����� � ����� �������� ������ ���������� ������������� ��� �������� ���������� �� ������ �������

#ifdef _DEBUG
	//���� ��� ������� ����� �����
	class testWavelengthInTheLine {
		//��������, ��� ����� ����� ������ ����
		//frequency - ������� ������������� �������, ��
		//epsilon - ��������������� ������������� �����������
		static void check(double frequency, double epsilon)noexcept {
			double const value = wavelengthInTheLine(frequency, epsilon);
			assert(value > 0);
		}
		//�������� ����� ����� � ������� ���������� �������� (� �������� ���������)
		//frequency - ������� ������������� �������, ��
		//epsilon - ��������������� ������������� �����������
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double frequency, double epsilon, double result, double precision) {
			double const value = wavelengthInTheLine(frequency, epsilon);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testWavelengthInTheLine() {
			test();
		}

		static void test()noexcept {
			check(1e6, 2.0);
			check(1e9, 1.0);
			check(7e8, 3.5);

			checkEqual(8.5e9, 2.08, 0.0244721, 1e-4);
			checkEqual(1e10, 2.08, 0.0208013, 1e-4);
		}
	} test_WavelengthInTheLine;
#endif // _DEBUG


	//������������ ������� �������� ��������������� ����� � ����� ��������, �/�
	//epsilon - ��������������� ������������� �����������
	double phaseSpeed(double const epsilon) {
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");

		double const result = lightSpeed / sqrt(epsilon);
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ������� ��������
	class testPhaseSpeed {
		//��������, ��� ������� �������� ������ ����
		//epsilon - ��������������� ������������� �����������
		static void check(double epsilon)noexcept {
			double const value = phaseSpeed(epsilon);
			assert(value > 0);
		}
		//�������� � ������� ���������� �������� (� �������� ���������)
		//epsilon - ��������������� ������������� �����������
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double epsilon, double result, double precision) {
			double const value = phaseSpeed(epsilon);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testPhaseSpeed() {
			test();
		}

		static void test()noexcept {
			check(2.0);
			check(1.0);
			check(3.5);

			checkEqual(1.0, lightSpeed, 1);
			checkEqual(4, lightSpeed / 2, 1);
		}
	} test_PhaseSpeed;
#endif // _DEBUG


	//������������������ ������������� ������, ��
	//epsilon - ��������������� ������������� �����������
	double characteristicResistance(double const epsilon) {
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");

		double const result = 120.0 * M_PI * sqrt(1.0 / epsilon);
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ������������������� �������������
	class testCharacteristicResistance {
		//��������, ��� ������������������ ������������� ������ ����
		//epsilon - ��������������� ������������� �����������
		static void check(double epsilon)noexcept {
			double const value = characteristicResistance(epsilon);
			assert(value > 0);
		}
		//�������� � ������� ���������� �������� (� �������� ���������)
		//epsilon - ��������������� ������������� �����������
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double epsilon, double result, double precision) {
			double const value = characteristicResistance(epsilon);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testCharacteristicResistance() {
			test();
		}

		static void test()noexcept {
			check(2.0);
			check(1.0);
			check(3.5);

			checkEqual(2.08, 261.3963, 1e-3);
		}
	} test_CharacteristicResistance;
#endif // _DEBUG


	//�������� ����������� ��������� ����� � ����������� �����, ��/�
	//tanDelta - ������� ���� ������ � �����������
	//wavelength - ����� �����, �
	double attenuationCoefficientInDielectric(double const tanDelta, double const wavelength) {
		if (tanDelta <= 0.0)
			throw exception(L"������� ���� ������ ������ ���� ������ 0");
		if (wavelength <= 0.0)
			throw exception(L"����� ����� ������ ���� ������ 0");
		
		//����������� ���������, ��/�
		double const alpha_d = tanDelta * M_PI / wavelength;
		//��������� � ��/�
		double result = alpha_d * 8.68;
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ��������� ������������ ��������� ����� � ����������� �����
	class testAttenuationCoefficientInDielectric {
		//��������, ��� �������� ����������� ��������� ������ ����
		//tanDelta - ������� ���� ������ � �����������
		//wavelength - ����� �����, �
		static void check(double const tanDelta, double const wavelength)noexcept {
			double const value = attenuationCoefficientInDielectric(tanDelta, wavelength);
			assert(value > 0);
		}
		//�������� � ������� ���������� �������� (� �������� ���������)
		//tanDelta - ������� ���� ������ � �����������
		//wavelength - ����� �����, �
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double const tanDelta, double const wavelength, double result, double precision) {
			double const value = attenuationCoefficientInDielectric(tanDelta, wavelength);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testAttenuationCoefficientInDielectric() {
			test();
		}

		static void test()noexcept {
			check(0.00001, 0.001);
			check(0.00001, 0.1);
			check(0.001, 1.1);

			checkEqual(2.5e-4, 0.0244721, 0.2788, 1e-3);
			checkEqual(2.5e-4, 0.0208013, 0.328, 1e-3);
		}
	} test_AttenuationCoefficientInDielectric;
#endif // _DEBUG


	//�������� ����������� ��������� ����� � ������������� �������, ��/�
	//frequency - ������� ������������� �������, ��
	//sigma - ������������ �������, ��/� (������ �� ����)
	//epsilon - ��������������� ������������� �����������
	//d - ������� ���������� ���� ������, �
	//D - ������� ����������� ������, �
	//D ������ ���� ������ ��� d
	double attenuationCoefficientInMetal(double const frequency, double const sigma, double const epsilon, double const d, double const D) {
		if (frequency <= 0.0)
			throw exception(L"������� ������ ���� ������ 0");
		if (sigma <= 0.0)
			throw exception(L"������������ ������ ���� ������ 0");
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");
		if (D <= d)
			throw exception(L"������� ������� ������ ���� ������ �����������");
		if (d <= 0)
			throw exception(L"���������� ������� ������ ���� ������ 0");

		//������� �������, ���/�
		double const omega = 2.0 * M_PI * frequency;

		//������������� ������������� �������, ��
		double const R_superficial = sqrt((omega * magneticConstant) / (2.0 * sigma));

		//������ � �������, ��/�
		double const alpha_m = sqrt(epsilon) * (R_superficial / d + R_superficial / D) / (120.0 * M_PI * log(D / d));

		//��������� � ��/�
		double const result = alpha_m * 8.68;
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ��������� ������������ ��������� ����� � ������� �����
	class testAttenuationCoefficientInMetal {
		//��������, ��� �������� ����������� ��������� ������ ����
		//frequency - ������� ������������� �������, ��
		//sigma - ������������ �������, ��/� (������ �� ����)
		//epsilon - ��������������� ������������� �����������
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		static void check(double const frequency, double const sigma, double const epsilon, double const d, double const D)noexcept {
			double const value = attenuationCoefficientInMetal(frequency, sigma, epsilon, d, D);
			assert(value > 0);
		}
		//�������� � ������� ���������� �������� (� �������� ���������)
		//frequency - ������� ������������� �������, ��
		//sigma - ������������ �������, ��/� (������ �� ����)
		//epsilon - ��������������� ������������� �����������
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double const frequency, double const sigma, double const epsilon, double const d, double const D, double result, double precision) {
			double const value = attenuationCoefficientInMetal(frequency, sigma, epsilon, d, D);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testAttenuationCoefficientInMetal() {
			test();
		}

		static void test()noexcept {
			check(1e6, 1e6, 1, 1, 2);
			check(1e9, 1e7, 1, 10, 20);
			check(2e9, 1e8, 1, 1, 5);

			checkEqual(1e10, 6.1e7, 2.08, 2.1e-3, 7.3e-3, 0.416, 1e-3);
			checkEqual(8.5e9, 6.1e7, 2.08, 2.1e-3, 7.3e-3, 0.383, 1e-3);
		}
	} test_AttenuationCoefficientInMetal;
#endif // _DEBUG


	//�������� ����������� ����� ������
	//tanDelta - ������� ���� ������ � �����������
	//frequency - ������� ������������� �������, ��
	//sigma - ������������ �������, ��/� (������ �� ����)
	//epsilon - ��������������� ������������� �����������
	//d - ������� ���������� ���� ������, �
	//D - ������� ����������� ������, �
	//D ������ ���� ������ ��� d
	double totalAttenuationCoefficient(double const tanDelta, double const frequency, double const sigma, double const epsilon, double const d, double const D) {
		if (tanDelta <= 0.0)
			throw exception(L"������� ���� ������ ������ ���� ������ 0");
		if (frequency <= 0.0)
			throw exception(L"������� ������ ���� ������ 0");
		if (sigma <= 0.0)
			throw exception(L"������������ ������ ���� ������ 0");
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");
		if (D <= d)
			throw exception(L"������� ������� ������ ���� ������ �����������");
		if (d <= 0)
			throw exception(L"���������� ������� ������ ���� ������ 0");

		//����� ����� � ����� ��������
		double const wavelength = wavelengthInTheLine(frequency, epsilon);
		//������ � ����������
		double const dielectricLosses = attenuationCoefficientInDielectric(tanDelta, wavelength);
		//������ � �������
		double const metalLosses = attenuationCoefficientInMetal(frequency, sigma, epsilon, d, D);
		double const result = dielectricLosses + metalLosses;
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ��������� ������������ ��������� ����� � �����
	class testTotalAttenuationCoefficient {
		//��������, ��� �������� ����������� ��������� ������ ����
		//tanDelta - ������� ���� ������ � �����������
		//frequency - ������� ������������� �������, ��
		//sigma - ������������ �������, ��/� (������ �� ����)
		//epsilon - ��������������� ������������� �����������
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		static void check(double const tanDelta, double const frequency, double const sigma, double const epsilon, double const d, double const D)noexcept {
			double const value = totalAttenuationCoefficient(tanDelta, frequency, sigma, epsilon, d, D);
			assert(value > 0);
		}
		//�������� � ������� ���������� �������� (� �������� ���������)
		//tanDelta - ������� ���� ������ � �����������
		//frequency - ������� ������������� �������, ��
		//sigma - ������������ �������, ��/� (������ �� ����)
		//epsilon - ��������������� ������������� �����������
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double const tanDelta, double const frequency, double const sigma, double const epsilon, double const d, double const D, double result, double precision) {
			double const value = totalAttenuationCoefficient(tanDelta, frequency, sigma, epsilon, d, D);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testTotalAttenuationCoefficient() {
			test();
		}

		static void test()noexcept {
			check(1e-3, 1e6, 1e6, 1, 1, 2);
			check(1e-4, 1e9, 1e7, 1, 10, 20);
			check(1e-2, 2e9, 1e8, 1, 1, 5);

			checkEqual(2.5e-4, 1e10, 6.1e7, 2.08, 2.1e-3, 7.3e-3, 0.744, 1e-3);
			checkEqual(2.5e-4, 8.5e9, 6.1e7, 2.08, 2.1e-3, 7.3e-3, 0.6618, 1e-3);
		}
	} test_TotalAttenuationCoefficient;
#endif // _DEBUG


	//�������� �������������
	//epsilon - ��������������� ������������� �����������
	//d - ������� ���������� ���� ������, �
	//D - ������� ����������� ������, �
	//D ������ ���� ������ ��� d
	double waveResistance(double const epsilon, double const d, double const D) {
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");
		if (D <= d)
			throw exception(L"������� ������� ������ ���� ������ �����������");
		if (d <= 0)
			throw exception(L"���������� ������� ������ ���� ������ 0");

		double const result = 60.0 * sqrt(1.0 / epsilon) * log(D / d);
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ��������� �������������
	class testWaveResistance {
		//��������, ��� �������� ������������� ������ ����
		//epsilon - ��������������� ������������� �����������
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		static void check(double const epsilon, double const d, double const D)noexcept {
			double const value = waveResistance(epsilon, d, D);
			assert(value > 0);
		}
		//�������� � ������� ���������� �������� (� �������� ���������)
		//epsilon - ��������������� ������������� �����������
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		//result - ��������� ���������
		//precision - ���������� ������� �����������
		static void checkEqual(double const epsilon, double const d, double const D, double result, double precision) {
			double const value = waveResistance(epsilon, d, D);
			double const delta = abs(value - result);
			assert(delta <= precision);
		}
	public:
		testWaveResistance() {
			test();
		}

		static void test()noexcept {
			check(1, 1, 2);
			check(2, 10, 20);
			check(3, 1, 5);

			checkEqual(2.08, 2.1e-3, 7.3e-3, 51.834, 1e-3);
			checkEqual(2.08, 1.5e-3, 4.86e-3, 48.907, 1e-3);
		}
	} test_WaveResistance;
#endif // _DEBUG


	//������� ���������, ��� ��� ������� �������� ���������� � ��������, ��� ���� �� ����������� �������� ������. � ���������� �������� ������ ������� ������

	//������� ����������, �
	//Ep - ������������� ���������, �/�
	//d - ������� ���������� ���� ������, �
	//D - ������� ����������� ������, �
	//D ������ ���� ������ ��� d
	double peakVoltage(double const Ep, double const d, double const D) {
		if (Ep <= 0)
			throw exception(L"������������� ��������� ������ ���� ������ 0");
		if (D <= d)
			throw exception(L"������� ������� ������ ���� ������ �����������");
		if (d <= 0)
			throw exception(L"���������� ������� ������ ���� ������ 0");

		double const result = Ep * (D / 2.0) * log(D / d);
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� �������� ����������
	class testPeakVoltage {
		//��������, ��� ������� ���������� ������ ����
		//Ep - ������������� ���������, �/�
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		static void check(double const Ep, double const d, double const D)noexcept {
			double const value = peakVoltage(Ep, d, D);
			assert(value > 0);
		}
	public:
		testPeakVoltage() {
			test();
		}

		static void test()noexcept {
			check(2.5e7, 1, 2);
			check(5e7, 10, 20);
			check(3e7, 1, 5);
		}
	} test_PeakVoltage;
#endif // _DEBUG


	//������� ��������
	//epsilon - ��������������� ������������� �����������
	//Ep - ������������� ���������, �/�
	//d - ������� ���������� ���� ������, �
	//D - ������� ����������� ������, �
	//D ������ ���� ������ ��� d
	double peakPower(double const epsilon, double const Ep, double const d, double const D) {
		if (epsilon < 1.0)
			throw exception(L"��������������� ������������� ������ ���� ������ ��� ����� 1");
		if (Ep <= 0)
			throw exception(L"������������� ��������� ������ ���� ������ 0");
		if (D <= d)
			throw exception(L"������� ������� ������ ���� ������ �����������");
		if (d <= 0)
			throw exception(L"���������� ������� ������ ���� ������ 0");

		//������� ����������
		double const u = peakVoltage(Ep, d, D);
		double result = (u * u / 120.0) * sqrt(epsilon / log(D / d));
		return result;
	}

#ifdef _DEBUG
	//���� ��� ������� ������� ��������
	class testPeakPower {
		//��������, ��� ������� ���������� ������ ����
		//Ep - ������������� ���������, �/�
		//d - ������� ���������� ���� ������, �
		//D - ������� ����������� ������, �
		static void check(double const Ep, double const d, double const D)noexcept {
			double const value = peakVoltage(Ep, d, D);
			assert(value > 0);
		}
	public:
		testPeakPower() {
			test();
		}

		static void test()noexcept {
			check(2.5e7, 1, 2);
			check(5e7, 10, 20);
			check(3e7, 1, 5);
		}
	} test_PeakPower;
#endif // _DEBUG
}