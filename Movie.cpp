/*****************************************
** File:    Movie.cpp
** Description: This file implements the functions outlined in Movie.h in order to create a funcioning Movie class
***********************************************/

#include "Movie.h"
#include <iostream>
#include <string>

using namespace std;

// Default Constructor
Movie::Movie()
    : m_title(""), m_rating(""), m_genre(""), m_year(0), m_director(""), m_star(""),
      m_budget(0), m_gross(0), m_studio(""), m_runtime(0) {}

// Overloaded Constructor
Movie::Movie(string title, string rating, string genre, int year, string director,
             string star, long budget, long gross, string studio, int runtime)
    : m_title(title), m_rating(rating), m_genre(genre), m_year(year), m_director(director),
      m_star(star), m_budget(budget), m_gross(gross), m_studio(studio), m_runtime(runtime) {}

// Accessors
string Movie::GetTitle() const { return m_title; }
string Movie::GetRating() const { return m_rating; }
string Movie::GetGenre() const { return m_genre; }
int Movie::GetYear() const { return m_year; }
string Movie::GetDirector() const { return m_director; }
string Movie::GetStar() const { return m_star; }
long Movie::GetBudget() const { return m_budget; }
long Movie::GetGross() const { return m_gross; }
string Movie::GetStudio() const { return m_studio; }
int Movie::GetRuntime() const { return m_runtime; }

// Mutators
void Movie::SetTitle(string title) { m_title = title; }
void Movie::SetRating(string rating) { m_rating = rating; }
void Movie::SetGenre(string genre) { m_genre = genre; }
void Movie::SetYear(int year) { m_year = year; }
void Movie::SetDirector(string director) { m_director = director; }
void Movie::SetStar(string star) { m_star = star; }
void Movie::SetBudget(long budget) { m_budget = budget; }
void Movie::SetGross(long gross) { m_gross = gross; }
void Movie::SetStudio(string studio) { m_studio = studio; }
void Movie::SetRuntime(int runtime) { m_runtime = runtime; }

// Overloaded << Operator
ostream &operator<<(ostream &out, Movie &m)
{
  out << m.GetTitle() << " by " << m.GetDirector() << " from " << m.GetYear();
  return out;
}

// Overloaded < Operator
bool Movie::operator<(const Movie &m)
{
  return m_year < m.m_year;
}

bool Movie::operator>(const Movie &m)
{
  return m_year > m.m_year;
}
