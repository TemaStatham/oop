#include "CCStringList.h"

CCStringList::CCStringList(const CCStringList& other)
{
	CopyList(other);
}

CCStringList::CCStringList(CCStringList&& other) noexcept
{
	MoveList(std::move(other));
}

// Операторы присваивания (копирующий и перемещающий)
CCStringList& CCStringList::operator=(const CCStringList& other)
{
	if (this != &other)
	{
		Clear();
		CopyList(other);
	}
	return *this;
}

CCStringList& CCStringList::operator=(CCStringList&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		MoveList(std::move(other));
	}
	return *this;
}

// Деструктор
CCStringList ::~CCStringList()
{
	Clear();
}

// Добавление строки в начало списка
void CCStringList::PushFront(const std::string& value)
{
	auto newNode = std::make_shared<Node>();
	newNode->data = value;

	if (m_first == nullptr)
	{
		m_first = newNode;
		m_last = newNode;
	}
	else
	{
		newNode->next = m_first;
		m_first->prev = newNode;
		m_first = newNode;
	}

	++m_size;
}

// Добавление строки в конец списка
void CCStringList::PushBack(const std::string& value)
{
	auto newNode = std::make_shared<Node>();
	newNode->data = value;

	if (m_last == nullptr)
	{
		m_first = newNode;
		m_last = newNode;
	}
	else
	{
		newNode->prev = m_last;
		m_last->next = newNode;
		m_last = newNode;
	}

	++m_size;
}

// Узнать количество элементов
size_t CCStringList::GetSize() const
{
	return m_size;
}

// Проверка, является ли список пустым
bool CCStringList::IsEmpty() const
{
	return m_size == 0;
}

// Удалить все элементы из списка
void CCStringList::Clear()
{
	while (m_first != nullptr)
	{
		m_first = m_first->next;
	}

	m_last = nullptr;
	m_size = 0;
}

// Вставка элемента в позицию, задаваемую итератором
void CCStringList::Insert(const std::string& value, const std::shared_ptr<Node>& pos)
{
	if (pos == nullptr)
	{
		PushBack(value);
		return;
	}

	auto newNode = std::make_shared<Node>();
	newNode->data = value;

	newNode->prev = pos->prev;
	newNode->next = pos;
	pos->prev = newNode;

	if (newNode->prev != nullptr)
	{
		newNode->prev->next = newNode;
	}
	else
	{
		m_first = newNode;
	}

	++m_size;
}

// Удаление элемента в позиции, задаваемой итератором
void CCStringList::Erase(const std::shared_ptr<Node>& pos)
{
	if (pos == nullptr)
	{
		return;
	}

	if (pos->prev != nullptr)
	{
		pos->prev->next = pos->next;
	}
	else
	{
		m_first = pos->next;
	}

	if (pos->next != nullptr)
	{
		pos->next->prev = pos->prev;
	}
	else
	{
		m_last = pos->prev;
	}

	--m_size;
}

// Получение итератора, указывающего на начало списка
std::shared_ptr<CCStringList::Node> CCStringList::begin() const
{
	return m_first;
}

// Получение итератора, указывающего на конец списка
std::shared_ptr<CCStringList::Node> CCStringList::end() const
{
	return nullptr;
}

// Получение реверсированного итератора, указывающего на начало списка
std::shared_ptr<CCStringList::Node> CCStringList::rbegin() const
{
	return m_last;
}

// Получение реверсированного итератора, указывающего на конец списка
std::shared_ptr<CCStringList::Node> CCStringList::rend() const
{
	return nullptr;
}

// Вспомогательная функция для копирования списка
void CCStringList::CopyList(const CCStringList& other)
{
	CCStringList tmp = other;
	for (const auto& value : tmp)
	{
		PushBack(value);
	}
}

// Вспомогательная функция для перемещения списка
void CCStringList::MoveList(CCStringList&& other) noexcept
{
	m_first = std::move(other.m_first);
	m_last = std::move(other.m_last);
	m_size = other.m_size;

	other.m_first = nullptr;
	other.m_last = nullptr;
	other.m_size = 0;
}
