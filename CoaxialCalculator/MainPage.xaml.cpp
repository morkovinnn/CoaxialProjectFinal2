//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Coaxial.h"

using namespace CoaxialCalculator;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x419

//Конструктор главной страницы
MainPage::MainPage() {
	InitializeComponent();
}

//Преобразует строку платформы UWP в число с плавающей точкой
//strPtr - указатель на строку платформы UWP
template<typename StrPtr>
double ToDouble(StrPtr strPtr) {
	const wchar_t* begin = strPtr->Data();
	return std::wcstod(begin, nullptr);
}

//Преобразуетс строку в стиле C в строку платформы UWP
//cstr - указатель на строку в стиле C
String^ To_String(wchar_t const* cstr) {
	String^ result = ref new String(cstr);
	return result;
}

//Метод обработки события нажатия на кнопку "Рассчитать!"
void CoaxialCalculator::MainPage::ButtonStart_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	try {
		//..Считываем исходные данные
		//Внутренний диаметр, м
		double const d = ToDouble(TextBox_d->Text) * 1e-3;
		//Внешний диаметр, м
		double const D = ToDouble(TextBox_D->Text) * 1e-3;
		//Рабочая частота, Гц
		double const f = ToDouble(TextBox_F->Text) * 1e9;
		//Проводимость металла, См/м
		double const sigma = ToDouble(TextBox_sigma->Text) * 1e6;
		//Диэлектрическая проницаемость
		double const epsilon = ToDouble(TextBox_epsilon->Text);
		//Электрическая прочность, В/м
		double const Ep = ToDouble(TextBox_ep->Text) * 1e6;
		//Тангенс угла потерь
		double const tanDelta = ToDouble(TextBox_tanDelta->Text);

		//Длина волны
		double const lambda = Coaxial::wavelengthInTheLine(f, epsilon);//м
		double const lambda_output = lambda * 1e3;//мм
		//Фазовая скорость
		double const vfl = Coaxial::phaseSpeed(epsilon);//м/с
		double const vfl_output = vfl * 1e-3;//км/с
		//Характеристическое сопротивление, Ом
		double const zc = Coaxial::characteristicResistance(epsilon);
		//Затухание в диэлектрике, дБ/м
		double const alpha_d = Coaxial::attenuationCoefficientInDielectric(tanDelta, lambda);
		//Затухание в металле, дБ/м
		double const alpha_m = Coaxial::attenuationCoefficientInMetal(f, sigma, epsilon, d, D);
		//Общее затухание, дБ/м
		double const alpha = Coaxial::totalAttenuationCoefficient(tanDelta, f, sigma, epsilon, d, D);
		//Волновое сопротивление, Ом
		double const rho = Coaxial::waveResistance(epsilon, d, D);
		//Пиковое напряжение
		double const Umax = Coaxial::peakVoltage(Ep, d, D);//В
		double const Umax_output = Umax * 1e-3;//кВ
		//Пиковая мощность
		double const Pmax = Coaxial::peakPower(epsilon, Ep, d, D);//Вт
		double const Pmax_output = Pmax * 1e-6;//МВт

		//..Вывод результатов расчётов
		TextBlock_lambda->Text = lambda_output.ToString();
		TextBlock_vfl->Text = vfl_output.ToString();
		TextBlock_zct->Text = zc.ToString();
		TextBlock_alpha_d->Text = alpha_d.ToString();
		TextBlock_alpha_m->Text = alpha_m.ToString();
		TextBlock_alpha_sum->Text = alpha.ToString();
		TextBlock_rho->Text = rho.ToString();
		TextBlock_Umax->Text = Umax_output.ToString();
		TextBlock_Pmax->Text = Pmax_output.ToString();
	}
	catch (Coaxial::exception const& e) {
		ContentDialog^ dialog = ref new ContentDialog;
		dialog->Title = "Введено некорректное значение";
		dialog->Content = To_String(e.what());
		dialog->CloseButtonText = "Ok";
		
		dialog->ShowAsync();
	}
}
