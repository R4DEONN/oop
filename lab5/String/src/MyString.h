#pragma once

#include "string"

class MyString
{
public:
	// конструктор по умолчанию
	MyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	MyString(const char * pString); // NOLINT(*-explicit-constructor)

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	MyString(const char * pString, size_t length);

	// конструктор копирования
	MyString(MyString const& other);

	// перемещающий конструктор
	//  реализуется совместно с перемещающим оператором присваивания
	MyString(MyString && other) noexcept;

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	MyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~MyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	[[nodiscard]] size_t GetLength() const noexcept;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	[[nodiscard]] const char* GetStringData() const noexcept;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	[[nodiscard]] MyString SubString(size_t start, size_t length = SIZE_MAX)const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	// Возвращает вместимость строки
	[[nodiscard]] size_t GetCapacity() const noexcept;

	MyString& operator=(MyString const& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString operator+(const MyString& other) const;
	MyString operator+(const std::string& other) const;
	MyString operator+(const char* other) const;
	MyString operator+(char ch) const;
	MyString& operator+=(const MyString& other);
	bool operator==(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator>=(const MyString& other) const;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);

private:
	char* m_chars;
	size_t m_size;
	size_t m_capacity;

	static char m_nullChar;

	MyString(size_t size, size_t capacity, char* m_chars);
};