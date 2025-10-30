#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

// Parse a line: grade credits
bool parseCourse(const string& line, double& grade, int& credits) {
    if (line.empty()) return false;

    grade = -1; credits = -1;
    int read = sscanf(line.c_str(), "%lf %d", &grade, &credits);
    if (read != 2 || grade < 0 || credits <= 0) return false;

    // cap grades at 10
    if (grade > 10) grade = 10;
    return true;
}

// Compute the CGPA and print details
double computeCGPA(ifstream& fin, int n, ofstream& fout) {
    double weighted_sum = 0.0, total_credits = 0.0;
    string line;

    fout << "Course details:\n";
    fin.ignore(256, '\n');

    for (int i = 0; i < n && getline(fin, line); ++i) {
        double grade; int credits;

        if (!parseCourse(line, grade, credits)) {
            fout << "  Course " << i + 1 << " -> invalid or skipped\n";
            continue;
        }

        fout << "  Course " << i + 1
             << " -> Grade: " << grade
             << ", Credits: " << credits << "\n";

        weighted_sum += grade * credits;
        total_credits += credits;
    }

    fout << "---------------------\n";
    fout << "Total Credits: " << total_credits << "\n";

    if (total_credits == 0)
        return 0.0;

    double cgpa = weighted_sum / total_credits;
    // round to two decimals
    return round(cgpa * 100) / 100.0;
}

int main(int argc, char* argv[]) {
    string infile = (argc > 1) ? argv[1] : "cgpa.in";
    ifstream fin(infile);

    if (!fin.is_open()) {
        cout << "File not found. Switching to manual input mode.\n";
        cout << "Enter number of courses: ";

        int n;
        if (!(cin >> n) || n <= 0) {
            cout << "Invalid input.\n";
            return 0;
        }

        double weighted_sum = 0.0, total_credits = 0.0;

        for (int i = 0; i < n; ++i) {
            double grade; int credits;
            cout << "Course " << i + 1 << " grade and credits: ";
            if (!(cin >> grade >> credits)) {
                cout << "Invalid data, skipping.\n";
                cin.clear();
                cin.ignore(256, '\n');
                continue;
            }

            if (grade < 0 || credits <= 0) {
                cout << "Skipped (invalid values).\n";
                continue;
            }
            if (grade > 10) grade = 10;

            weighted_sum += grade * credits;
            total_credits += credits;
        }

        if (total_credits == 0) {
            cout << "CGPA: 0.00\n";
            return 0;
        }

        double cgpa = round((weighted_sum / total_credits) * 100) / 100.0;
        cout << "---------------------\n";
        cout << "Total Credits: " << total_credits << "\n";
        cout << "CGPA: " << fixed << setprecision(2) << cgpa << "\n";
        return 0;
    }

    ofstream fout("cgpa.out");
    int n;
    if (!(fin >> n)) {
        fout << "Invalid input.\n";
        fout << "CGPA: 0.00\n";
        return 0;
    }

    if (n <= 0) {
        fout << "No valid courses.\n";
        fout << "CGPA: 0.00\n";
        return 0;
    }

    double cgpa = computeCGPA(fin, n, fout);
    fout << "CGPA: " << fixed << setprecision(2) << cgpa << "\n";

    return 0;
}
