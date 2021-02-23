#pragma once

#include "Vector2.h"

struct Branch {
public:
	Branch(int startScore) : m_Score(startScore) {}

	//setters
	void SetBranch(Vector2 vector2, int score) {
		m_Pos = vector2;
		m_Score = score;

		IS_SET = true;
	}

	//getters
	const int GetScore() const {
		return m_Score;
	}
	const Vector2 GetPosition() const {
		return m_Pos;
	}
	const bool isSet() const {
		return IS_SET;
	}

private:
	int m_Score;
	Vector2 m_Pos = Vector2(0, 0);

	bool IS_SET = false;
};