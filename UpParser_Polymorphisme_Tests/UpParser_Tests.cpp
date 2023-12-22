#include "pch.h"
#include "gtest/gtest.h"
#include "../UpParser_Polymorphisme_Lib/HelpCommand.h"

class Toto : public Command {
public:
    Toto() : Command("TOTO", { "-toto" }, 0, "Print 'Toto Tata Titi !'", false, true) {}
    void processArgs(const std::vector<std::string>& args)  {}
    void execute()  {
        std::cout << "Toto Tata Titi !" << std::endl;
    }
};

class HelloCommand : public Command {
private:
    std::string nameToHello;
public:
    HelloCommand() : Command("hello", { "-hello" }, 1, "Print 'Hello, [Arg] !'", true, false) {}

    void processArgs(const std::vector<std::string>& args) {
        nameToHello = args[0];
    }

    void execute() {
        std::cout << "Hello, " << nameToHello << "!" << std::endl;
    }
};

namespace COO_Parser_Tests {

    // Test for immediate command execution.
    TEST(ParsingTest, ImmediateCommandExecution) {
        Parsing parsing;
        HelpCommand helpCommand(&parsing);
        parsing.addCommand(&helpCommand);
  

        char* argv[] = { "executableImmediateCommandExecution", "-h" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        parsing.parseCommandLine(argc, argv);

        // Check if the HelpCommand is processed as expected.
        ASSERT_TRUE(helpCommand.isProcessed());
    }

    // Test for non-immediate command execution.
    TEST(ParsingTest, NonImmediateCommandExecution) {
        Parsing parsing;
        HelpCommand helpCommand(&parsing);
        parsing.addCommand(&helpCommand);
        Toto toto;
        parsing.addCommand(&toto);

        char* argv[] = { "executableNonImmediateCommandExecution","-toto", "arg1", "arg2", "-h" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        parsing.parseCommandLine(argc, argv);

        // Check if Toto command and HelpCommand are processed as expected.
        ASSERT_TRUE(toto.isProcessed());
        ASSERT_TRUE(helpCommand.isProcessed());
    }

    // Test for detecting the absence of a required command.
    TEST(ParsingTest, MissingRequiredCommand) {
        Parsing parsing;
        HelpCommand helpCommand(&parsing);
        parsing.addCommand(&helpCommand);
        HelloCommand hello;
        parsing.addCommand(&hello);

        char* argv[] = { "executableMissingRequiredCommand" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        // Check if an exception is thrown when a required command is missing.
        ASSERT_THROW(parsing.parseCommandLine(argc, argv), std::invalid_argument);
    }

    // Test for encountering a nonexistent command.
    TEST(ParsingTest, NonExistentCommand) {
        Parsing parsing;
        char* argv[] = { "executableNonExistentCommand", "-nonExistentCommand" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        // Check if an exception is thrown when encountering a nonexistent command.
        ASSERT_THROW(parsing.parseCommandLine(argc, argv), std::invalid_argument);
    }

    // Test for executing a command and checking if an exception is thrown (negative case).
    TEST(ParsingTest, ExecuteCommande) {
        Parsing parsing;

        HelloCommand hello;
        parsing.addCommand(&hello);

        char* argv[] = { "executableExecuteCommande", "-nonExistentCommand" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        // Add assertions to check if an exception is thrown for the nonexistent command.
        ASSERT_THROW(parsing.parseCommandLine(argc, argv), std::invalid_argument);
    }

    // Test for executing a command and checking the return value (positive case).
    TEST(ParsingTest, ExecuteCommandeReturn) {
        Parsing parsing;

        HelloCommand hello;
        parsing.addCommand(&hello);

        char* argv[] = { "executableExecuteCommande", "-hello", "mazen", "file1"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        // Call parseCommandLine to simulate the execution of the command.
        parsing.parseCommandLine(argc, argv);

        // Capture the output of the execute function.
        std::ostringstream outputCapture;
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputCapture.rdbuf());

        // Call the execute function.
        hello.execute();

        // Restore the standard output buffer.
        std::cout.rdbuf(coutBuffer);

        // Check if the output of the execute function is equal to the expected value.
        ASSERT_EQ(outputCapture.str(), "Hello, mazen!\n");
    }
}
