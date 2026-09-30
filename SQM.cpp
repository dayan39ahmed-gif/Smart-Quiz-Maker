#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string generateUserName(const std::string &role) {
  int number = 1000 + (rand() % 9000);
  return role + std::to_string(number);
}

std::string generatePassword() {
  std::string chars =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  std::string password;
  for (int i = 0; i < 8; i++) {
    password += chars[rand() % chars.length()];
  }
  return password;
}

std::string toUpper(std::string str) {
  for (char &c : str) {
    c = std::toupper(c);
  }
  return str;
}

void printHeader(std::string title) {
  std::cout << "\n";
  std::cout << std::string(50, '=') << "\n";

  int titleLength = title.length();
  int totalSpaces = 50 - titleLength;
  int leftSpaces = totalSpaces / 2;

  for (int i = 0; i < leftSpaces; i++) {
    std::cout << " ";
  }
  std::cout << title;
  for (int i = 0; i < totalSpaces - leftSpaces; i++) {
    std::cout << " ";
  }
  std::cout << "\n";
  std::cout << std::string(50, '=') << "\n\n";
}

void updateUser(std::string role) {
  std::string userName, fileUser, fileID, filePass, fileName, fileSub, fileDeg,
      fileSec, FileName;
  int fileExp, fileSem;
  long long fileCon;

  if (role == "ADMIN")
    FileName = "adminsdata.txt";
  else if (role == "TEACHER")
    FileName = "teachersdata.txt";
  else if (role == "STUDENT")
    FileName = "studentsdata.txt";
  printHeader("UPDATE INFO OF " + role + " PORTAL");
  std::cout << "Enter the username of the target user: ";
  std::cin >> userName;

  std::ifstream readfile(FileName);
  std::ofstream writefile("temp.txt");
  if (!readfile) {
    std::cout << "The file could not be opened\n";
  }

  bool found = false;
  if (role == "ADMIN") {
    while (readfile >> fileID >> fileUser >> filePass >> fileName >> fileExp >>
           fileCon) {
      if (userName == fileUser) {
        found = true;
        std::cout << "MATCH FOUND!\n\n";

        fileUser = generateUserName("ADM");
        filePass = generatePassword();

        std::cout << " Enter new first name: ";
        std::cin >> fileName;
        std::cout << " Enter your new number of years of experience: ";
        std::cin >> fileExp;
        std::cout << " Enter your new contact number: ";
        std::cin >> fileCon;

        std::cout << "Your new data has been entered!\n\n";
        std::cout << "Your new username: ";
        std::cout << fileUser << '\n';
        std::cout << "Your new password: ";
        std::cout << filePass << '\n';
      }
      writefile << fileID << " " << fileUser << " " << filePass << " "
                << fileName << " " << fileExp << " " << fileCon << '\n';
    }
  }
  if (role == "TEACHER") {
    while (readfile >> fileID >> fileUser >> filePass >> fileName >> fileSub >>
           fileExp >> fileCon) {
      if (userName == fileUser) {
        found = true;
        std::cout << "MATCH FOUND!\n\n";

        fileUser = generateUserName("TEA");
        filePass = generatePassword();

        std::cout << " Enter new first name: ";
        std::cin >> fileName;
        std::cout << " Enter your new subject: ";
        std::cin >> fileSub;
        std::cout << " Enter your new number of years of experience: ";
        std::cin >> fileExp;
        std::cout << " Enter your new contact number: ";
        std::cin >> fileCon;

        std::cout << "Your new data has been entered!\n\n";
        std::cout << "Your new username: ";
        std::cout << fileUser << '\n';
        std::cout << "Your new password: ";
        std::cout << filePass << '\n';
      }
      writefile << fileID << " " << fileUser << " " << filePass << " "
                << fileName << " " << fileSub << " " << fileExp << " "
                << fileCon << '\n';
    }
  }
  if (role == "STUDENT") {
    while (readfile >> fileID >> fileUser >> filePass >> fileName >> fileDeg >>
           fileSem >> fileSec >> fileCon) {
      if (userName == fileUser) {
        found = true;
        std::cout << "MATCH FOUND!\n\n";

        fileUser = generateUserName("STU");
        filePass = generatePassword();

        std::cout << " Enter new first name: ";
        std::cin >> fileName;
        std::cout << " Enter new degree program: ";
        std::cin >> fileDeg;
        std::cout << " Enter new semester: ";
        std::cin >> fileSem;
        std::cout << " Enter new section: ";
        std::cin >> fileSec;
        std::cout << " Enter your new contact number: ";
        std::cin >> fileCon;

        std::cout << "Your new data has been entered!\n\n";
        std::cout << "Your new username: ";
        std::cout << fileUser << '\n';
        std::cout << "Your new password: ";
        std::cout << filePass << '\n';
      }
      writefile << fileID << " " << fileUser << " " << filePass << " "
                << fileName << " " << fileDeg << " " << fileSem << " "
                << fileSec << fileCon << '\n';
    }
  }

  readfile.close();
  writefile.close();

  if (found == false) {
    std::cout << "No such user found\n";
    std::remove("temp.txt");
  } else {
    std::remove(FileName.c_str());
    std::rename("temp.txt", FileName.c_str());
  }
  return;
}

void checkResult() {
  std::string userName, fileUser, quizSub, fileSub, quizTitle, fileTitle, total,
      fileTotal, result, fileResult;

  printHeader("RESULT ANNOUNCEMENT PORTAL");
  std::cout << "Enter your username: ";
  std::cin >> userName;
  std::cout << "Enter the subject (In Capital Letters): ";
  std::cin >> quizSub;
  std::cout << "Enter the title (In Capital Letters): ";
  std::cin >> quizTitle;

  std::ifstream check("answersoresults.txt");
  if (!check) {
    std::cout << "The file could not be opened\n";
  }

  bool found = false;
  while (std::getline(check, fileUser)) {
    std::getline(check, fileSub);
    std::getline(check, fileTitle);
    std::getline(check, fileResult);
    std::getline(check, fileTotal);
    if (userName == fileUser && quizSub == fileSub && quizTitle == fileTitle) {
      result = fileResult;
      total = fileTotal;
      found = true;
      break;
    }
  }

  if (!found) {
    std::cout << "The results have not been declared yet!\n";
  } else {
    std::cout << "You have scored: ";
    std::cout << result << " out of " << total << " in " << quizSub << "("
              << quizTitle << ")" << '\n';
  }
  check.close();
  return;
}

void takeQuiz() {
  std::string userName;
  std::string studentDeg, fileDeg, studentSec, fileSec;
  std::string quizSub, fileSub, fileTitle, quizTitle, subject;
  int fileTimer = 0, fileQs = 0, fileMarks = 0, fileTime = 0;

  printHeader("QUIZ CONDUCTION PORTAL");
  std::cout << "Which subject's quiz would you like to take first? (In Capital "
               "Letters): ";
  std::cin >> subject;
  std::cout << "What is your degree program? (In Capital Letters): ";
  std::cin >> studentDeg;
  std::cout << "What is your section? (In Capital Letters): ";
  std::cin >> studentSec;

  std::string tempQuizVer = subject + "_verification.txt";
  std::ifstream verify(tempQuizVer);
  if (!verify) {
    std::cout << "The file could not be opened\n";
    return;
  }

  bool eligible = false;
  while (verify >> fileSub >> fileTitle >> fileTimer >> fileQs >> fileMarks >>
         fileDeg >> fileSec) {
    if (studentDeg == fileDeg && studentSec == fileSec) {
      eligible = true;
      quizSub = fileSub;
      quizTitle = fileTitle;
      fileTime = fileTimer;
      break;
    }
    verify.ignore(1000, '\n');
  }
  verify.close();

  time_t startTime = time(nullptr);
  int timeLimit = fileTime * 60;
  time_t endTime = startTime + timeLimit;

  if (!eligible) {
    std::cout << "You are not eligible for this quiz\n";
    return;
  }

  std::cout << "You are eligible for this quiz\n";
  std::cout << "Enter your username before taking the quiz: ";
  std::cin >> userName;

  std::string finalQuizFile = quizSub + "_Quiz.txt";
  std::ifstream file(finalQuizFile);
  if (!file) {
    std::cout << "The file could not be opened\n";
    return;
  }
  int count = 0;
  std::string questions[20];
  std::string options[20][4];
  int correctAns[20];
  int totalQuestions = 0;

  std::string question, o1, o2, o3, o4;
  int correct;
  while (std::getline(file, question) && totalQuestions < 20) {
    std::getline(file, o1);
    std::getline(file, o2);
    std::getline(file, o3);
    std::getline(file, o4);
    file >> correct;
    file.ignore(1000, '\n');

    questions[totalQuestions] = question;
    options[totalQuestions][0] = o1;
    options[totalQuestions][1] = o2;
    options[totalQuestions][2] = o3;
    options[totalQuestions][3] = o4;
    correctAns[totalQuestions] = correct - 1;

    totalQuestions++;
  }
  file.close();

  if (totalQuestions == 0) {
    std::cout << "No questions!\n";
    return;
  }
  bool used[20] = {false};
  int score = 0;
  int marksPerQ = fileMarks / totalQuestions;

  for (int i = 0; i < totalQuestions; i++) {
    if (time(nullptr) >= endTime) {
      std::cout << "<-------------QUIZ ENDED AUTOMATICALLY------------>\n\n";
      break;
    }
    int remaining = endTime - time(nullptr);
    std::cout << "Time remaining: " << remaining << " seconds\n";

    int qIndex;
    do {
      qIndex = rand() % totalQuestions;
    } while (used[qIndex]);

    used[qIndex] = true;

    std::cout << "\nQuestion " << (i + 1) << " / " << totalQuestions << ":\n";
    std::cout << questions[qIndex] << "\n\n";
    int optOrder[4] = {0, 1, 2, 3};
    for (int x = 0; x < 10; x++) {
      int a = rand() % 4;
      int b = rand() % 4;
      int temp = optOrder[a];
      optOrder[a] = optOrder[b];
      optOrder[b] = temp;
    }
    for (int j = 0; j < 4; j++) {
      std::cout << (j + 1) << ". " << options[qIndex][optOrder[j]] << "\n";
    }

    std::cout << "\nYour answer (1-4): ";
    int answer;
    std::cin >> answer;
    while (answer < 1 || answer > 4) {
      std::cout << "Enter 1-4: ";
      std::cin >> answer;
    }
    answer--;

    if (optOrder[answer] == correctAns[qIndex]) {
      std::cout << "Correct!\n";
      count += 2;
    } else {
      std::cout << "Wrong!\n";
    }

    std::cout << "Press Enter...\n";
    std::cin.ignore();
    std::cin.get();
  }
  std::ofstream result("tempanswersoresults.txt", std::ios::app);
  if (!result) {
    std::cout << "The file could not be opened\n\n";
  } else {
    result << userName << '\n'
           << quizSub << '\n'
           << quizTitle << '\n'
           << count << '\n'
           << fileMarks << '\n';
  }
}

void studentPanel() {

  int choiceStudent;
  printHeader("WELCOME TO STUDENT DASHBOARD");
  std::cout << "1. Take Quiz\n";
  std::cout << "2. View My Result\n";
  std::cout << "3. Update Information\n";
  std::cout << "0. Logout\n";

  std::cout << "Enter Your Choice (0-3): ";
  std::cin >> choiceStudent;

  switch (choiceStudent) {
  case 1:
    takeQuiz();
    studentPanel();
    break;
  case 2:
    checkResult();
    studentPanel();
    break;
  case 3:
    updateUser("STUDENT");
    studentPanel();
    break;
  case 0:
    break;
  default:
    std::cout << "That was not a valid response\n";
  }
}

void announceResults() {
  std::string userName, fileSub, fileTitle, fileTotal, fileMarks;
  printHeader("RESULTS ANNOUNCEMENTS PORTAL");

  std::ifstream read("tempanswersoresults.txt");
  std::ofstream write("answersoresults.txt");

  if (!read) {
    std::cout << "The file could not be opened\n";
  }

  while (read >> userName >> fileSub >> fileTitle >> fileMarks >> fileTotal) {
    write << userName << '\n'
          << fileSub << '\n'
          << fileTitle << '\n'
          << fileMarks << '\n'
          << fileTotal << '\n';
  }
  read.close();
  write.close();

  std::remove("tempanswersoresults.txt");

  std::cout << '\n';
  std::cout << "THIS IS AN IMPORTANT ANNOUNCEMENT:\n";
  std::cout << "                                             __\n";
  std::cout << "  ___      __                               |  |          __\n";
  std::cout << "   |    _ |__|  _ _      _ _  | | _      _  |_|  _ _     |__|  "
               "        _         _ _  _ \n";
  std::cout << "   ||_||_ ||_  |_|_ | || ||_  |-||_||  ||_  | | |_|_|* | |  "
               "||* | |* || || ||* || |_ | |\n";
  std::cout << "   || ||_ |  |_|_ _||_||_| _| | || | || |_  |__||_|_| *| |  || "
               "*| | *||_||_|| *||_|_ |_| \n";
  return;
}

void cancelQuiz(std::string subject, std::string title) {
  std::string fileSub, fileTitle, fileDeg, fileSec;
  int fileTime, fileQs, fileMarks;
  printHeader("CANCELLING THE QUIZ PORTAL");

  std::string tempQuizVer = subject + "_verification.txt";
  std::ifstream read(tempQuizVer);
  std::ofstream write("temp.txt");

  if (!read) {
    std::cout << "The file could not be opened\n";
    return;
  }

  bool found = false;
  while (read >> fileSub >> fileTitle >> fileTime >> fileQs >> fileMarks >>
         fileDeg >> fileSec) {
    if (subject == fileSub && title == fileTitle) {
      found = true;
      continue;
    }
    write << fileSub << " " << fileTitle << " " << fileTime << " " << fileQs
          << " " << fileMarks << " " << fileDeg << " " << fileSec << '\n';
  }

  read.close();
  write.close();

  if (found == 1) {
    std::remove(tempQuizVer.c_str());
    std::rename("temp.txt", tempQuizVer.c_str());
    std::string quizFile = "temp" + subject + "_Quiz.txt";
    std::remove(quizFile.c_str());
    std::cout << "Quiz cancelled successfully!\n\n";
  } else {
    std::remove("temp.txt");
  }
  return;
}

void changeQuizReqs(std::string subject, std::string title) {
  std::string fileSub, fileTitle, fileDeg, fileSec;
  int fileTime, fileQs, fileMarks;
  printHeader("CHANGE REQUIREMENTS OF QUIZ PORTAL");
  std::string tempQuizVer = subject + "_verification.txt";
  std::ifstream read(tempQuizVer);
  std::ofstream write("temp.txt");

  if (!read) {
    std::cout << "The file could not be opened!\n";
  }

  bool found = false;
  while (read >> fileSub >> fileTitle >> fileTime >> fileQs >> fileMarks >>
         fileDeg >> fileSec) {
    if (subject == fileSub && title == fileTitle) {
      std::cout << "\nENTER NEW DETAILS:\n";
      std::cout << " Timer (minutes): ";
      std::cin >> fileTime;
      std::cout << " Total questions: ";
      std::cin >> fileQs;
      std::cout << " Total marks: ";
      std::cin >> fileMarks;
      std::cout << " Degree program: ";
      std::cin >> fileDeg;
      std::cout << " Section: ";
      std::cin >> fileSec;

      fileDeg = toUpper(fileDeg);
      fileSec = toUpper(fileSec);

      found = true;
    }

    write << fileSub << " " << fileTitle << " " << fileTime << " " << fileQs
          << " " << fileMarks << " " << fileDeg << " " << fileSec << '\n';
  }

  read.close();
  write.close();

  if (found) {
    std::remove(tempQuizVer.c_str());
    std::rename("temp.txt", tempQuizVer.c_str());
    std::cout << "\nRequirements changed successfully!\n";
  } else {
    std::remove("temp.txt");
    std::cout << "\nQuiz not found!\n";
  }
  return;
}

void changeInQuiz(std::string quizFile) {
  std::string targetQuestion;
  printHeader("CHANGE QUESTION IN QUIZ PORTAL");

  std::ifstream display(quizFile);
  if (!display) {
    std::cout << "The file could not be opened\n";
    return;
  }

  std::string question, option1, option2, option3, option4, correctOption;
  while (std::getline(display, question)) {
    std::getline(display, option1);
    std::getline(display, option2);
    std::getline(display, option3);
    std::getline(display, option4);
    std::getline(display, correctOption);

    std::cout << "Question: " << question << "\n\n";
  }
  display.close();

  std::cout << "Enter the question you want to change: ";
  std::getline(std::cin >> std::ws, targetQuestion);

  std::ifstream read(quizFile);
  std::ofstream write("temp.txt");

  if (!read) {
    std::cout << "The file could not be opened\n";
    return;
  }

  bool found = false;
  while (std::getline(read, question)) {
    std::getline(read, option1);
    std::getline(read, option2);
    std::getline(read, option3);
    std::getline(read, option4);
    std::getline(read, correctOption);

    if (question == targetQuestion) {
      std::cout << "Enter new Question: ";
      std::getline(std::cin, question);
      std::cout << "Enter new Option 1: ";
      std::getline(std::cin, option1);
      std::cout << "Enter new Option 2: ";
      std::getline(std::cin, option2);
      std::cout << "Enter new Option 3: ";
      std::getline(std::cin, option3);
      std::cout << "Enter new Option 4: ";
      std::getline(std::cin, option4);
      std::cout << "Enter new Correct Option: ";
      std::getline(std::cin, correctOption);

      found = true;
    }

    write << question << '\n'
          << option1 << '\n'
          << option2 << '\n'
          << option3 << '\n'
          << option4 << '\n'
          << correctOption << '\n';
  }

  read.close();
  write.close();

  if (found) {
    std::remove(quizFile.c_str());
    std::rename("temp.txt", quizFile.c_str());
    std::cout << "Question changed successfully!\n";
  } else {
    std::remove("temp.txt");
    std::cout << "Question not found\n";
  }
  return;
}

void removeFromQuiz(std::string quizFile) {
  std::string targetQuestion;
  std::string question, option1, option2, option3, option4, correctOption;
  printHeader("REMOVE QUESTION FROM QUIZ PORTAL");

  std::cout << "Enter the question text to remove: ";
  std::getline(std::cin >> std::ws, targetQuestion);

  std::ifstream read(quizFile);
  std::ofstream write("temp.txt");

  if (!read) {
    std::cout << "The file could not be opened\n";
    return;
  }

  bool found = false;
  while (std::getline(read, question)) {
    std::getline(read, option1);
    std::getline(read, option2);
    std::getline(read, option3);
    std::getline(read, option4);
    std::getline(read, correctOption);

    if (question == targetQuestion) {
      found = true;
      continue; // Skip writing this question
    }

    write << question << '\n'
          << option1 << '\n'
          << option2 << '\n'
          << option3 << '\n'
          << option4 << '\n'
          << correctOption << '\n';
  }

  read.close();
  write.close();

  if (found) {
    std::remove(quizFile.c_str());
    std::rename("temp.txt", quizFile.c_str());
    std::cout << "Question removed successfully!\n";
  } else {
    std::remove("temp.txt");
    std::cout << "Question not found\n";
  }
  return;
}

void addToQuiz(std::string quizFile) {
  int num;
  std::string question, opt1, opt2, opt3, opt4;
  int correctOption;
  printHeader("ADD QUESTIONS TO QUIZ PORTAL");

  std::cout << "How many questions do you want to add?: ";
  std::cin >> num;

  std::ofstream file(quizFile, std::ios::app);
  if (!file) {
    std::cout << "The file could not be opened!\n";
    return;
  }

  for (int i = 0; i < num; i++) {
    std::cout << "Question " << i + 1 << ": ";
    std::getline(std::cin >> std::ws, question);

    std::cout << "Option 1: ";
    std::getline(std::cin, opt1);
    std::cout << "Option 2: ";
    std::getline(std::cin, opt2);
    std::cout << "Option 3: ";
    std::getline(std::cin, opt3);
    std::cout << "Option 4: ";
    std::getline(std::cin, opt4);

    std::cout << "Correct option (1-4): ";
    std::cin >> correctOption;

    while (correctOption < 1 || correctOption > 4) {
      std::cout << "Invalid! Enter correct option again (1-4): ";
      std::cin >> correctOption;
    }

    file << question << '\n'
         << opt1 << '\n'
         << opt2 << '\n'
         << opt3 << '\n'
         << opt4 << '\n'
         << correctOption << '\n';
  }

  file.close();
  std::cout << "Questions added successfully!\n";
  return;
}

void quizUpdate() {
  std::string subject, title, degree, section;
  printHeader("QUIZ UPDATE PORTAL");

  std::cout << "Enter the subject: ";
  std::getline(std::cin >> std::ws, subject);
  std::cout << "Enter the title: ";
  std::getline(std::cin >> std::ws, title);
  std::cout << "Enter degree program: ";
  std::getline(std::cin >> std::ws, degree);
  std::cout << "Enter section: ";
  std::cin >> section;

  subject = toUpper(subject);
  title = toUpper(title);
  degree = toUpper(degree);
  section = toUpper(section);
  std::string tempQuizVer = subject + "_verification.txt";
  std::ifstream file(tempQuizVer);
  if (!file) {
    std::cout << "The file could not be opened!\n";
    return;
  }

  bool found = false;
  std::string fileSub, fileTitle, fileDeg, fileSec;
  int fileTime, fileQs, fileMarks;
  int questions = 0;

  while (std::getline(file, fileSub)) {
    std::getline(file, fileTitle);
    file >> fileTime >> fileQs >> fileMarks >> fileDeg >> fileSec;
    if (subject == fileSub && title == fileTitle && degree == fileDeg &&
        section == fileSec) {
      found = true;
      break;
    }
    questions = fileQs;
  }
  file.close();

  if (!found) {
    std::cout << "\nNo such quiz found!\n\n";
    return;
  }

  std::cout << "\nMATCH FOUND\n\n";
  std::cout << "What do you want to do?: \n";
  std::cout << " 1. Add questions to quiz\n";
  std::cout << " 2. Remove questions from quiz\n";
  std::cout << " 3. Change a question in quiz\n";
  std::cout << " 4. Change quiz requirements\n";
  std::cout << " 5. Cancel Quiz\n";
  std::cout << " 0. Exit\n";
  std::cout << "  Enter your choice (0-5): ";

  int choice;
  while (!(std::cin >> choice)) {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Invalid input. Enter a number: ";
  }

  std::string quizFile = "temp" + subject + "_Quiz.txt";
  if (!file)
    std::cout << "The file could not be opened!\n";
  else {
    switch (choice) {
    case 1:
      addToQuiz(quizFile);
      break;
    case 2:
      removeFromQuiz(quizFile);
      break;
    case 3:
      changeInQuiz(quizFile);
      break;
    case 4:
      changeQuizReqs(subject, title);
      break;
    case 5:
      cancelQuiz(subject, title);
      break;
    case 0:
      break;
    default:
      std::cout << "That was not a valid response\n";
    }
  }
  return;
}

void quizPreview() {
  int choiceTeacher;
  std::string fileQuestion, fileOption1, fileOption2, fileOption3, fileOption4,
      fileCorrectOption;
  std::string quizSub, quizTitle;
  printHeader("QUIZ PREVIEW PORTAL");

  std::cout << "Enter subject name: ";
  std::getline(std::cin >> std::ws, quizSub);
  std::cout << "Enter quiz title: ";
  std::getline(std::cin >> std::ws, quizTitle);

  quizSub = toUpper(quizSub);
  quizTitle = toUpper(quizTitle);
  std::string tempQuizVer = quizSub + "_verification.txt";
  std::ifstream verify(tempQuizVer);
  if (!verify) {
    std::cout << "The file could not be opened\n";
  }
  bool found = false;
  std::string line, fileSub, fileTitle, fileTimer, fileQs, fileMarks, fileDeg,
      fileSec;

  while (std::getline(verify, fileSub)) {
    std::getline(verify, fileTitle);
    std::getline(verify, fileTimer);
    std::getline(verify, fileQs);
    std::getline(verify, fileMarks);
    std::getline(verify, fileDeg);
    std::getline(verify, fileSec);
    if (quizSub == fileSub && quizTitle == fileTitle) {
      found = true;
    } else {
      found = false;
    }
  }
  if (found == false) {
    std::cout << "No such quiz found\n";
  } else {
    std::string tempFileName = "temp" + quizSub + "_Quiz.txt";
    std::string finalFileName = quizSub + "_Quiz.txt";

    std::ifstream preview(tempFileName);

    if (!preview) {
      std::cout << "The file could not be opened\n\n";
    }

    std::cin.ignore();

    while (std::getline(preview, fileQuestion)) {
      std::getline(preview, fileOption1);
      std::getline(preview, fileOption2);
      std::getline(preview, fileOption3);
      std::getline(preview, fileOption4);
      std::getline(preview, fileCorrectOption);

      std::cout << "Question: " << fileQuestion << '\n';
      std::cout << "Option 1: " << fileOption1 << '\n';
      std::cout << "Option 2: " << fileOption2 << '\n';
      std::cout << "Option 3: " << fileOption3 << '\n';
      std::cout << "Option 4: " << fileOption4 << '\n';
      std::cout << "Correct Option: " << fileCorrectOption << "\n\n";
    }
    std::cout << " Are you satisfied with the quiz?: \n";
    std::cout << " 1. Yes\n";
    std::cout << " 2. No\n";
    std::cout << " 0. Back\n";

    std::cin >> choiceTeacher;

    if (choiceTeacher == 1) {

      std::ifstream read(tempFileName);
      std::ofstream write(finalFileName, std::ios::app);

      if (!read) {
        std::cout << "The file could not be opened\n";
      }
      if (!write) {
        std::cout << "the file could not be opened\n";
      }

      while (std::getline(read, fileQuestion)) {
        std::getline(read, fileOption1);
        std::getline(read, fileOption2);
        std::getline(read, fileOption3);
        std::getline(read, fileOption4);
        std::getline(read, fileCorrectOption);

        write << fileQuestion << '\n'
              << fileOption1 << '\n'
              << fileOption2 << '\n'
              << fileOption3 << '\n'
              << fileOption4 << '\n'
              << fileCorrectOption << '\n';
      }
      std::cout << "Quiz Uploaded Successfully!\n\n";

      std::ofstream empty(tempFileName, std::ios::trunc);
      empty.close();
    } else if (choiceTeacher == 2) {
      std::ofstream empty(tempFileName, std::ios::trunc);
      empty.close();

      std::cout << "The quiz was not uploaded\n";
    } else if (choiceTeacher == 0) {
      return;
    } else {
      std::cout << "That was not a valid response\n\n";
    }
    preview.close();
  }
  return;
}

void quizCreation() {
  std::string quizSub, quizTitle;
  int quizTime, quizTotalQs, quizTotalMarks;
  std::string quizEligibleDegree, quizEligibleSection;
  std::string quizQuestion, quizOption1, quizOption2, quizOption3, quizOption4,
      quizCorrectOption;
  std::string text;
  std::string options[4];
  int correctOption;
  printHeader("QUIZ CREATION PORTAL");

  std::cout << "Quiz Subject: ";
  std::getline(std::cin >> std::ws, quizSub);
  std::cout << "Quiz Title: ";
  std::getline(std::cin >> std::ws, quizTitle);
  std::cout << "Time Limit (In Minutes): ";
  std::cin >> quizTime;
  std::cout << "Total Questions (Max 20): ";
  std::cin >> quizTotalQs;
  std::cout << "Total Marks: ";
  std::cin >> quizTotalMarks;
  std::cout << "Which degree program is eligible for this quiz?: ";
  std::cin >> quizEligibleDegree;
  std::cout << "Which section is eligible for this quiz?: ";
  std::cin >> quizEligibleSection;
  std::cout << '\n';

  quizSub = toUpper(quizSub);
  quizTitle = toUpper(quizTitle);
  quizEligibleDegree = toUpper(quizEligibleDegree);
  quizEligibleSection = toUpper(quizEligibleSection);

  std::string tempFileName = "temp" + quizSub + "_Quiz.txt";
  std::string tempQuizVer = quizSub + "_verification.txt";
  std::ofstream verify(tempQuizVer);

  if (!verify) {
    std::cout << "the file could not be opened\n";
  }

  verify << quizSub << '\n'
         << quizTitle << '\n'
         << quizTime << '\n'
         << quizTotalQs << '\n'
         << quizTotalMarks << '\n'
         << quizEligibleDegree << '\n'
         << quizEligibleSection << '\n';

  verify.close();

  std::ofstream file(tempFileName);

  if (!file) {
    std::cout << "The file could not be opened\n";
  }

  for (int i = 0; i < quizTotalQs; i++) {
    std::cout << "Question " << i + 1 << ": ";
    std::getline(std::cin >> std::ws, text);

    for (int j = 0; j < 4; j++) {
      std::cout << "Option " << j + 1 << ": ";
      std::getline(std::cin, options[j]);
    }

    std::cout << "Correct Option (1-4): ";
    std::cin >> correctOption;

    while (correctOption < 1 || correctOption > 4) {
      std::cout << "Invalid Response!\n";
      std::cout << "Enter correct option again (1-4): ";
      std::cin >> correctOption;
    }

    file << text << '\n';

    for (int i = 0; i < 4; i++) {
      file << options[i] << '\n';
    }

    file << correctOption << '\n';
    std::cout << '\n';
  }
  std::cout << "Quiz Created Successfully!\n";
  file.close();
  return;
}

void teacherPanel() {
  int choiceTeacher;
  do {
    printHeader("WELCOME TO TEACHER DASHBOARD");

    std::cout << "1. Create A Quiz\n";
    std::cout << "2. Preview Quiz\n";
    std::cout << "3. Edit Quiz\n";
    std::cout << "4. Announce Results\n";
    std::cout << "5. Update Information\n";
    std::cout << "0. Logout\n";
    std::cout << "Enter Your Choice (0-5): ";
    while (!(std::cin >> choiceTeacher)) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Invalid Input. Enter a number: ";
    }

    switch (choiceTeacher) {
    case 1:
      quizCreation();
      break;
    case 2:
      quizPreview();
      break;
    case 3:
      quizUpdate();
      break;
    case 4:
      announceResults();
      break;
    case 5:
      updateUser("TEACHER");
    case 0:
      break;
    default:
      std::cout << "That was not a valid response\n";
    }
  } while (choiceTeacher != 0);
}

void listUsers(std::string role) {
  std::string filename;
  std::string fileID, fileUsername, filePassword, fileName;

  if (role == "ADMINS") {
    filename = "adminsdata.txt";
  } else if (role == "TEACHERS") {
    filename = "teachersdata.txt";
  } else if (role == "STUDENTS") {
    filename = "studentsdata.txt";
  } else {
    std::cout << "That was not a valid response\n";
  }

  printHeader("LIST OF ALL " + role);

  std::cout << "Here is the list of all the " << role << ":\n\n";

  std::ifstream file(filename);

  if (!file) {
    std::cout << "Error: Could not open file!\n\n";
  }
  while (file >> fileID >> fileUsername >> filePassword >> fileName) {
    std::cout << fileID << " | " << fileUsername << " | " << filePassword
              << " | " << fileName << "\n";
    file.ignore(1000, '\n');
  }
  file.close();
  return;
}

void removeUser(std::string role) {
  std::string username;
  std::string filename;
  if (role == "ADMIN") {
    filename = "adminsdata.txt";
  } else if (role == "TEACHER") {
    filename = "teachersdata.txt";
  } else if (role == "STUDENT") {
    filename = "studentsdata.txt";
  } else {
    std::cout << "Invalid role!\n\n";
    return;
  }

  printHeader("REMOVE " + role + " PORTAL");

  std::cout << "Enter the username of the target user: ";
  std::cin >> username;

  std::ifstream readfile(filename);
  std::ofstream writefile("temp.txt");

  if (!readfile) {
    std::cout << "The file could not be opened!\n\n";
    return;
  }

  bool found = false;
  std::string line;

  while (std::getline(readfile, line)) {
    std::string fileID, fileUser, filePass;
    std::istringstream iss(line);
    iss >> fileID >> fileUser >> filePass;

    if (username == fileUser) {
      found = true;
      std::cout << "\nUser has been removed!\n";
    } else {
      writefile << line << "\n";
    }
  }

  readfile.close();
  writefile.close();

  if (!found) {
    std::cout << "No such user found!\n\n";
    std::remove("temp.txt");
    return;
  }
  std::remove(filename.c_str());
  std::rename("temp.txt", filename.c_str());
  return;
}

void searchUser(std::string role) {
  std::string username;
  std::string filename;

  if (role == "ADMIN") {
    filename = "adminsdata.txt";
  } else if (role == "TEACHER") {
    filename = "teachersdata.txt";
  } else if (role == "STUDENT") {
    filename = "studentsdata.txt";
  } else {
    std::cout << "Invalid role!\n\n";
    return;
  }

  printHeader("SEARCH FOR " + role + " PORTAL");

  std::cout << "Enter the username: ";
  std::cin >> username;

  std::ifstream file(filename);
  if (!file) {
    std::cout << "Error: Could not open file!\n\n";
    return;
  }
  std::string fileID, fileUsername, filePassword;

  bool found = false;

  while (file >> fileID >> fileUsername >> filePassword) {
    if (username == fileUsername) {
      found = true;
      std::cout << "Match Found!\n\n";
      std::cout << "Your " << role << " ID is: " << fileID << "\n";
      std::cout << "Your username is: " << fileUsername << "\n";
      std::cout << "Your password is: " << filePassword << "\n\n";
      break;
    }
    file.ignore(1000, '\n');
  }

  file.close();

  if (!found) {
    std::cout << "User not found\n\n";
  }
  return;
}

void regUser(std::string role) {
  std::string fileName, fileID, fileUser;
  static int adminCount = 1, teacherCount = 1, studentCount = 1;
  int count;

  if (role == "ADMIN") {
    fileName = "adminsdata.txt";
    fileID = "ADMIN";
    fileUser = "ADM";
    count = adminCount++;
  } else if (role == "TEACHER") {
    fileName = "teachersdata.txt";
    fileID = "TEACHER";
    fileUser = "TEA";
    count = teacherCount++;
  } else if (role == "STUDENT") {
    fileName = "studentsdata.txt";
    fileID = "STUDENT";
    fileUser = "STU";
    count = studentCount++;
  } else {
    std::cout << "That was not a valid response\n";
  }

  std::string userName = generateUserName(role);
  std::string password = generatePassword();
  std::string userID = fileID + std::to_string(count);

  std::string name;
  int exp;
  long long con;

  printHeader("REGISTER " + role + " PORTAL");

  std::cout << "Enter your name: ";
  std::cin >> name;

  if (role == "TEACHER") {
    std::string subject;
    std::cout << "Enter subject: ";
    std::cin >> subject;
    subject = toUpper(subject);

    std::cout << "Years of experience: ";
    std::cin >> exp;
    std::cout << "Contact: ";
    std::cin >> con;

    std::ofstream file(fileName, std::ios::app);
    file << "\n"
         << userID << " " << userName << " " << password << " " << name << " "
         << subject << " " << exp << " " << con;
    file.close();
  } else if (role == "STUDENT") {
    std::string degree, section;
    int semester;

    std::cout << "Enter degree program (AI, EE, etc.): ";
    std::cin >> degree;
    do {
      std::cout << "Enter semester (1-8): ";
      std::cin >> semester;
    } while (semester < 1 || semester > 8);
    std::cout << "Enter section: ";
    std::cin >> section;
    std::cout << "Contact: ";
    std::cin >> con;

    degree = toUpper(degree);
    section = toUpper(section);

    std::ofstream file(fileName, std::ios::app);
    file << "\n"
         << userID << " " << userName << " " << password << " " << name << " "
         << degree << " " << semester << " " << section << " " << con;
    file.close();
  } else {
    std::cout << "Years of experience as admin: ";
    std::cin >> exp;
    std::cout << "Contact: ";
    std::cin >> con;

    std::ofstream file(fileName, std::ios::app);
    file << "\n"
         << userID << " " << userName << " " << password << " " << name << " "
         << exp << " " << con;
    file.close();
  }

  std::cout << "\nRegistered successfully as " << role << "!\n";
  std::cout << "ID      : " << userID << "\n";
  std::cout << "Username: " << userName << "\n";
  std::cout << "Password: " << password << "\n\n";
  return;
}

void adminPanel() {
  int choiceAdmin, choiceAdmin2, choiceAdmin3, choiceAdmin4;
  do {
    printHeader("WELCOME TO ADMIN DASHBOARD");

    std::cout << "1. Register An Admin\n";
    std::cout << "2. Register A Teacher\n";
    std::cout << "3. Register A Student\n";
    std::cout << "4. Search For A User\n";
    std::cout << "5. Remove A User\n";
    std::cout << "6. Update Information\n";
    std::cout << "7. List Users\n";
    std::cout << "0. Logout\n";

    std::cout << " Enter your choice (0-7): ";
    while (!(std::cin >> choiceAdmin)) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Invalid input. Enter a number: ";
    }

    switch (choiceAdmin) {
    case 1:
      regUser("ADMIN");
      break;
    case 2:
      regUser("TEACHER");
      break;
    case 3:
      regUser("STUDENT");
      break;
    case 4:
      std::cout << "SEARCH FOR:\n";
      std::cout
          << " 1. Admin\n 2. Teacher\n 3. Student\n Enter your choice (1-3): ";
      std::cin >> choiceAdmin2;
      if (choiceAdmin2 == 1)
        searchUser("ADMIN");
      else if (choiceAdmin2 == 2)
        searchUser("TEACHER");
      else if (choiceAdmin2 == 3)
        searchUser("STUDENT");
      break;
    case 5:
      std::cout << '\n';
      std::cout << "REMOVE: \n";
      std::cout
          << " 1. Admin\n 2. Teacher\n 3. Student\n Enter your choice (1-3): ";
      std::cin >> choiceAdmin3;
      if (choiceAdmin3 == 1)
        removeUser("ADMIN");
      else if (choiceAdmin3 == 2)
        removeUser("TEACHER");
      else if (choiceAdmin3 == 3)
        removeUser("STUDENT");
      break;
    case 6:
      updateUser("ADMIN");
      break;
    case 7:
      std::cout << "LIST: \n";
      std::cout << " 1. Admins\n 2. Teachers\n 3. Students\n Enter your choice "
                   "(1-3): ";
      std::cin >> choiceAdmin4;
      if (choiceAdmin4 == 1)
        listUsers("ADMINS");
      else if (choiceAdmin4 == 2)
        listUsers("TEACHERS");
      else if (choiceAdmin4 == 3)
        listUsers("STUDENTS");
      break;
    case 0:
      break;
    default:
      std::cout << "That was not a valid response!\n";
    }
  } while (choiceAdmin != 0);
}

void userLogin(std::string role) {
  std::string fileName;
  if (role == "ADMIN")
    fileName = "adminsdata.txt";
  else if (role == "TEACHER")
    fileName = "teachersdata.txt";
  else if (role == "STUDENT")
    fileName = "studentsdata.txt";
  printHeader(role + " LOGIN PORTAL");

  std::string userID, userName, userPass;
  std::cout << "Enter your username: ";
  std::cin >> userName;
  std::cout << "Enter your password: ";
  std::cin >> userPass;

  std::ifstream file(fileName);
  if (!file) {
    std::cout << "The file could not be opened\n";
  }
  bool authentication = false;
  std::string fileID, fileUsername, filePassword;
  while (file >> fileID >> fileUsername >> filePassword) {
    if (userName == fileUsername && userPass == filePassword) {
      userID = fileID;
      authentication = true;
      break;
    }
    file.ignore(1000, '\n');
  }
  file.close();
  if (authentication == 1) {
    std::cout << userID << ": Login Successful!\n\n";
    if (role == "ADMIN")
      adminPanel();
    else if (role == "TEACHER")
      teacherPanel();
    else if (role == "STUDENT")
      studentPanel();
  } else {
    std::cout << "Invalid username or password!\n\n";
  }
}

int main() {
  srand(time(nullptr));
  int choice;
  do {
    printHeader("SMART QUIZ MAKER");
    std::ifstream checkFile("adminsdata.txt");
    if (!checkFile) {
      std::ofstream writeCheck("adminsdata.txt");
      writeCheck << "ADMIN0 Joker 1234 Heath 5 999";
      writeCheck.close();
      std::cout << "Default Admin Created:" << '\n'
                << " AdminID: ADMIN0" << '\n'
                << " Username: Joker" << '\n'
                << " Password: 1234\n\n";
    }
    checkFile.close();
    std::cout << "\nWhat feature do you want to access?\n";
    std::cout << "1. Login As An Admin\n";
    std::cout << "2. Login As A Teacher\n";
    std::cout << "3. Login As A Student\n";
    std::cout << "0. Exit\n";

    std::cout << " Enter your choice (0-3): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      std::cout << " You chose Admin Login\n";
      userLogin("ADMIN");
      break;
    case 2:
      std::cout << "You chose Teacher Login\n";
      userLogin("TEACHER");
      break;
    case 3:
      std::cout << "You chose Student Login\n";
      userLogin("STUDENT");
      break;
    case 0:
      printHeader("THANKS FOR USING");
      break;
    default:
      std::cout << "That was not a valid response!\n";
    }
  } while (choice != 0);
  return 0;
}