#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "sstream"

struct Point
{
	double x;
	double y;
};

/*
Интерфейс объектов, способных сохранять (SaveTo) и
восстанавливать (RestoreFrom) своё состояние из/в стандартных потоков чтения/записи
В случае ошибки выбрасывают исключения runtime_error
*/
class ISerializable
{
public:
	virtual void SaveTo(std::ostream& output) const = 0;

	virtual void RestoreFrom(std::istream& input) = 0;

protected:
	~ISerializable() = default;
};

/* Интерфейс холста. Позволяет рисовать отрезки прямых линий и эллипсы */
class ICanvas
{
public:
	virtual void DrawLine(Point from, Point to) const = 0;

	virtual void DrawEllipsis(Point center, double radius) const = 0;

protected:
	~ICanvas() = default;
};

/* Интерфейс объектов, которые могут быть нарисованы (Draw) на холсте (canvas) */
class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

protected:
	~ICanvasDrawable() = default;
};

/* Интерфейс объектов, умеющих говорить (Speak). */
class ISpeakable
{
public:
	virtual void Speak() const = 0;

protected:
	~ISpeakable() = default;
};

/* Прямоугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Rectangle : public ICanvasDrawable, public ISerializable /* Написать недостающий код */
{
public:
	Rectangle() = default;

	Rectangle(Point point, double width, double height)
		: m_point(point),
		  m_width(width),
		  m_height(height)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_point, {m_point.x + m_width, m_point.y});
		canvas.DrawLine({m_point.x + m_width, m_point.y}, {m_point.x + m_width, m_point.y + m_height});
		canvas.DrawLine({m_point.x, m_point.y + m_height}, {m_point.x + m_width, m_point.y + m_height});
		canvas.DrawLine({m_point.x, m_point.y + m_height}, m_point);
	}

	void SaveTo(std::ostream& output) const override
	{
		output << m_point.x << " " << m_point.y << " "
				  << m_width << " " << m_height << std::endl;
	}

	void RestoreFrom(std::istream& input) override
	{
		input >> m_point.x >> m_point.y >> m_width >> m_height;

		if (!input.good())
		{
			throw std::runtime_error("Error while read from std::cin");
		}
	}

private:
	Point m_point = { 0, 0 };
	double m_width = 0;
	double m_height = 0;
};

/* Эллипс. Может быть нарисован на холсте, а также является сериализуемым */
class Ellipse : public ICanvasDrawable, public ISerializable/* Написать недостающий код */
{
public:
	Ellipse(Point center, double radius)
		: m_center(center),
		  m_radius(radius)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawEllipsis(m_center, m_radius);
	}

	void SaveTo(std::ostream& output) const override
	{
		output << m_center.x << " " << m_center.y << " "
				  << m_radius << std::endl;
	}

	void RestoreFrom(std::istream& input) override
	{
		input >> m_center.x >> m_center.y >> m_radius;

		if (!input.good())
		{
			throw std::runtime_error("Error while read from std::cin");
		}
	}

private:
	Point m_center;
	double m_radius;
};

/* Треугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Triangle : public ICanvasDrawable, ISerializable/* Написать недостающий код */
{
public:
	Triangle(Point firstPoint, Point secondPoint, Point thirdPoint)
		: m_firstPoint(firstPoint),
		  m_secondPoint(secondPoint),
		  m_thirdPoint(thirdPoint)
	{

	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_firstPoint, m_secondPoint);
		canvas.DrawLine(m_thirdPoint, m_secondPoint);
		canvas.DrawLine(m_firstPoint, m_thirdPoint);
	}

	void SaveTo(std::ostream& output) const override
	{
		output << m_firstPoint.x << " " << m_firstPoint.y << " "
				  << m_secondPoint.x << " " << m_secondPoint.y << " "
				  << m_thirdPoint.x << " " << m_thirdPoint.y << std::endl;
	}

	void RestoreFrom(std::istream& input) override
	{
		input >> m_firstPoint.x >> m_firstPoint.y
				 >> m_secondPoint.x >> m_secondPoint.y
				 >> m_thirdPoint.x >> m_thirdPoint.y;

		if (!input.good())
		{
			throw std::runtime_error("Error while read from std::cin");
		}
	}

private:
	Point m_firstPoint;
	Point m_secondPoint;
	Point m_thirdPoint;
};

/* Холст. Вместо фактического рисования выводит в cout команды рисования и их параметры */
class CoutCanvas : public ICanvas /* Написать недостающий код */
{
public:
	void DrawLine(Point from, Point to) const override
	{
		std::cout
			<< "Line:" << std::endl
			<< "From: (" << from.x << ", " << from.y << ")" << std::endl
			<< "To: (" << to.x << ", " << to.y << ")" << std::endl << std::endl;
	}

	void DrawEllipsis(Point center, double radius) const override
	{
		std::cout
			<< "Ellipsis:" << std::endl
			<< "Center: (" << center.x << ", " << center.y << ")" << std::endl
			<< "Radius: " << radius << std::endl << std::endl;
	}
};

/* Кот. Обладает координатами (в центре головы). Может быть нарисован на холсте
 может говорить (мяукая) */
class Cat : public ICanvasDrawable, public ISpeakable
{
public:
	explicit Cat(Point point)
		: m_center(point)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawEllipsis(m_center, 10);
		Triangle triangle(
			{ m_center.x, m_center.y + 10 },
			{ m_center.x + 5, m_center.y + 20 },
			{ m_center.x + 5, m_center.y + 20 }
		);
		triangle.Draw(canvas);
	}

	void Speak() const override
	{
		std::cout << "Meow" << std::endl;
	}

private:
	Point m_center;
};

/* Человек. Обладает именем и годом рождения.
может говорить (называет своё имя и год рождения) */
class Person : public ISpeakable
{
public:
	Person(std::string fullName, std::string birthDate)
		: m_fullName(std::move(fullName)),
		  m_birthDate(std::move(birthDate))
	{
	}

	void Speak() const override
	{
		std::cout << "Hello) My name is " << m_fullName << ". I'm born in " << m_birthDate << " year!" << std::endl;
	}

private:
	std::string m_fullName;
	std::string m_birthDate;
};

/* Ведёт разговор с набором объектов, с которыми можно побеседовать */
void SmallTalk(const std::vector<ISpeakable*>& talkers)
{
	for (auto& talker: talkers)
	{
		talker->Speak();
	}
}

/* Рисует набор объектов, которые можно нарисовать на переданном холсте (принимает объекты и холст) */
void Draw(const std::vector<ICanvasDrawable*>& objects, ICanvas& canvas)
{
	for (auto obj: objects)
	{
		obj->Draw(canvas);
	}
}

/* Копирует состояние из одного сериализуемого объекта в другой */
void CopyState(const ISerializable& from, ISerializable& to)
{
	std::stringstream stream;
	from.SaveTo(stream);
	to.RestoreFrom(stream);
}

int main()
{
	/*
	Нарисовать при помощи функции Draw домик с котиком рядом с ним:
		/\
	   /  \
	  / O  \
	 --------
	  |    |
	  |    |
	  ------
	  до 8 баллов (8-6-4)
	*/
	CoutCanvas canvas;

	Triangle roof(
		{4, 0},
		{0, 3},
		{8, 3}
		);
	Ellipse window({3, 2}, 1);
	Rectangle houseWall({ 0, 3 }, 8, 4);
	Cat cat({ 10, 4 });

	Draw({&roof, &window, &houseWall, &cat}, canvas);

	/* Создать прямоугольник.
	 Скопировать в него при помощи CopyState состояние из прямоугольника,
	 задающего стены дома
	  до 6 баллов (6-5-3)
	*/
	Rectangle newRectangle;
	CopyState(houseWall, newRectangle);
	std::cout << "house wall: ";
	houseWall.SaveTo(std::cout);
	std::cout << std::endl;
	std::cout << "new rectangle: ";
	newRectangle.SaveTo(std::cout);
	std::cout << std::endl;

	/*
	Создать человека по имени Ivanov Ivan 1980 года рождения.
	При помощи SmallTalk побеседовать с этим человеком и вышесозданным котом
	  до 6 баллов (6-5-3)
	*/
	Person person("Ivanov Ivan", "1980");
	SmallTalk({ &person, &cat });

	return 0;
}