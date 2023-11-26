/*!******************************************************************
 * \file      process.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      26-11-2023
 *
 * \brief     Definitions for functions needed to print stats for students.
 *********************************************************************/
#include "process.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief Parses a file to create Student objects and organizes them into separate
 *        vectors for all students, undergraduates, and graduates.
 *
 * @param ifs An input file stream containing information about students.
 * @param vs A vector containing pointers to all created Student objects.
 * @param vus A vector containing pointers to only Undergraduate student objects.
 * @param vgs A vector containing pointers to only Graduate student objects.
 */
void parse_file(std::ifstream &ifs, std::vector<Student *> &vs,
                std::vector<Student *> &vus,
                std::vector<Student *> &vgs)
{
  std::string str;
  while (getline(ifs, str))
  {
    char ch = str[0];
    if (ch == 'U')
    {
      Student *ps = new Undergraduate(str);
      vs.push_back(ps); // vs will be used when all students
                        // are to be processed

      vus.push_back(ps); // vus will be used when only undergrads
                         // are to be processed
    }
    else if (ch == 'G')
    {
      Student *ps = new Graduate(str);
      vs.push_back(ps); // vs will be used when all student are
                        // to be processed

      vgs.push_back(ps); // vgs will be used when only grads are
                         // to be processed
    }
  }
}

/**
 * @brief Prints details of each student in the provided vector.
 *
 * @param students A vector containing pointers to Student objects.
 */
void print_records(const std::vector<Student *> &students)
{
  for (const auto &student : students)
  {
    student->print_details();
    std::cout << std::endl;
  }
}

/**
 * @brief Computes the mean of total scores for a vector of students.
 *
 * @param students A vector containing pointers to Student objects.
 *
 * @return A double representing the mean of total scores. If the vector is empty, returns 0.0.
 */
double compute_mean(const std::vector<Student *> &students)
{
  double total = 0.0;
  for (const auto &student : students)
  {
    total += student->total_score();
  }
  return students.empty() ? 0.0 : total / students.size();
}

/**
 * @brief Prints selected details of a student.
 *
 * @param student A pointer to a Student object.
 */
void print_student_details(const Student *student)
{
  std::cout << student->id() << ", " << student->name() << ", "
            << student->total_score() << ", " << student->course_grade() << std::endl;
}

/**
 * @brief Prints details of students in descending order of total scores.
 *
 * @param sorted_students A vector containing pointers to Student objects, sorted by total scores.
 */
void print_sorted_students(const std::vector<Student *> &sorted_students)
{
  std::cout << "The sorted list of students (id, name, total, grade) in descending order of total:" << std::endl;
  for (const auto &student : sorted_students)
  {
    print_student_details(student);
  }
  std::cout << std::endl;
}

/**
 * @brief Prints statistics and details of students.
 *
 * @param students A vector containing pointers to Student objects.
 */
void print_stats(const std::vector<Student *> &students)
{
  if (students.empty())
  {
    return;
  }

  std::cout << "Number of students = " << students.size() << std::endl;

  // Compute mean of total scores
  double mean = compute_mean(students);
  std::cout << "The mean of the total score = " << mean << std::endl;

  // Sorting students based on total score
  std::vector<Student *> sorted_students(students);
  std::sort(sorted_students.begin(), sorted_students.end(),
            [](const Student *a, const Student *b)
            {
              return a->total_score() > b->total_score();
            });

  // Print sorted students
  if (!sorted_students.empty())
  {
    print_sorted_students(sorted_students);
  }
}

/**
 * @brief Return memory allocated by operator new ONLY using pointers contained
 * in container specified by first parameter. Why? Because containers specified
 * in the next two containers reference the same memory locations as elements of
 * first container, double deletion will cause undefined run-time behavior.
 * Next, clear contents of all 3 containers.
 *
 * @param vs Reference to vector<Student*> containing pointers to all students.
 * @param vs Reference to vector<Student*> containing pointers to undergraduates.
 * @param vs Reference to vector<Student*> containing pointers to graduates.
 */
void cleanup(std::vector<Student *> &vs, std::vector<Student *> &vus, std::vector<Student *> &vgs)
{
  // delete memory previously allocated by operator new
  for (Student *ps : vs)
  {
    delete ps;
  }
  // avoid double deletion!!!
  vs.clear();
  vus.clear();
  vgs.clear();
}
