/*!******************************************************************
 * \file      student.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      26-11-2023
 *
 * \brief     Definitions for class Student member functions
 *********************************************************************/

#include "student.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// Initialize static data member scount
int Student::scount = 0;

/**
 * @brief Constructs a Student object from a comma-separated string.
 *
 * @param line A string containing comma-separated values (U/G, name, year of birth, project grade, homework grades).
 */
Student::Student(std::string &line)
{
    // Increment the student count
    scount++;
    sid = scount;

    // Use stringstream to parse the comma-separated values
    std::stringstream iss(line);
    std::string token;

    std::getline(iss, token, ',');            // Skip the U/G and remove leading spaces
    std::getline(iss >> std::ws, sname, ','); // Store name into sname and remove leading spaces
    std::getline(iss >> std::ws, token, ','); // Store the proj grades and hw grades into token

    syob = std::stoi(token);  // store year of birth
    iss >> token;             // reads next token from input stream iss
    sproj = std::stoi(token); // store grade for proj work

    std::stringstream hwgrades;
    std::getline(iss >> std::ws, token, ','); // store all the homework grades into token
    hwgrades << token;                        // set token string to be stringstream

    while (hwgrades >> token) // while not at the last grade
    {
        shw.push_back(std::stoi(token));
    }
}

/**
 * @brief Gets the ID of the student.
 *
 * @return An integer representing the student ID.
 */
int Student::id() const
{
    return sid;
}

/**
 * @brief Gets the name of the student.
 *
 * @return A string representing the student's name.
 */
std::string Student::name() const
{
    return sname;
}

/**
 * @brief Gets the year of birth of the student.
 *
 * @return An integer representing the student's year of birth.
 */
int Student::yob() const
{
    return syob;
}

/**
 * @brief Gets the project score of the student.
 *
 * @return A double representing the student's project score.
 */
double Student::project_score() const
{
    return sproj;
}

/**
 * @brief Gets the total count of created Student objects.
 *
 * @return An integer representing the total count of Student objects.
 */
int Student::count()
{
    return Student::scount;
}

/**
 * @brief Prints details of the student, including ID, name, age, project score,
 *        assignment grades, total score, and grade.
 */
void Student::print_details() const
{
    std::cout << "Id = " << id() << std::endl
              << "Name = " << name() << std::endl
              << "Age = " << this->age() << std::endl
              << "Project = " << sproj << std::endl
              << "Assignment = [";
    for (size_t i = 0; i < shw.size(); i++)
    {
        if (i != shw.size() - 1)
            std::cout << shw[i] << ", ";
        else
            std::cout << shw[i] << "]" << std::endl;
    }
    std::cout << "Total = " << this->total_score() << std::endl;
    std::cout << "Grade = " << this->course_grade() << std::endl;
}

/**
 * @brief Calculates the mean (average) of homework grades for the student.
 *
 * @return A double representing the mean of homework grades.
 *         If no homework grades are available, returns 0.0.
 */
double Student::hw_mean() const
{
    if (shw.empty())
    {
        return 0.0; // Handle the case when there are no homework grades
    }

    double sum = 0.0;
    for (const auto &grade : shw)
    {
        sum += grade;
    }

    return sum / shw.size();
}