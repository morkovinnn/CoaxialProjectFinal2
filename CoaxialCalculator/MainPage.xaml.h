//
// MainPage.xaml.h
// Объявление класса MainPage.
//

#pragma once

#include "MainPage.g.h"

namespace CoaxialCalculator
{
	/// <summary>
	/// Главная страница приложения (файл генерируется автоматически в VS 2019)
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		//Конструктор
		MainPage();

	private:
		//Метод обработки события нажатия на кнопку "Рассчитать!"
		void ButtonStart_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
