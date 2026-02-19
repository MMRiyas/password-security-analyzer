# Password Security Analyzer

A menu-driven password security analysis tool written in C. This program evaluates password strength using multiple real-world security techniques such as dictionary checks, entropy estimation, and pattern detection.

This project was developed as the Final Project for Harvard University's CS50x: Introduction to Computer Science.

---

## Author

M M Muhammed Riyas

---

## Demo

Video demonstration:  
https://youtu.be/BFGhQ4eRwh4

---

## Features

### Password Strength Analysis

The program analyzes a given password using several security checks:

- Password length evaluation
- Character variety analysis (uppercase, lowercase, digits, symbols)
- Dictionary attack simulation using common weak passwords
- Detection of repeated character patterns
- Detection of sequential character patterns
- Entropy estimation
- Overall strength scoring (0–100)
- Classification as Weak, Moderate, or Strong

### Secure Password Generator

The program can generate secure random passwords that include:

- Uppercase letters
- Lowercase letters
- Numbers
- Special characters

This helps users create stronger passwords resistant to brute-force attacks.

### Password Security Guidelines

Displays general best practices for creating secure passwords.

---

## Security Concepts Demonstrated

This project demonstrates several fundamental cybersecurity concepts:

- Dictionary attacks
- Brute-force resistance
- Password entropy
- Pattern-based password weaknesses
- Defensive programming
- Input validation
- File handling in C

---

## Project Structure

password-security-analyzer/
│
├── password_analyzer.c # Main source code
├── dictionary.txt # List of common weak passwords
├── README.md # Project documentation

---

## How It Works

The program uses a menu-driven interface with three main options:

1. Generate a secure password
2. Analyze an existing password
3. View password security guidelines

The analyzer evaluates password strength using multiple criteria and calculates an entropy score to estimate resistance against brute-force attacks.

---

## Compilation and Usage

### Compile

Using gcc:

gcc password_analyzer.c -lm -o password_analyzer

### Run

./password_analyzer

---

## Example

--- Password Security Analyzer ---

1. Generate secure password

2. Analyze password

3. Security guidelines

4. Exit

---

## Learning Outcomes

Through this project, I gained practical experience in:

- C programming
- File handling
- String manipulation
- Modular program design
- Security-focused thinking
- Implementing real-world security concepts

This project represents my early foundation in cybersecurity and secure software development.

---

## License

This project is for educational purposes.
