#include "pch.h"
#include "gtest/gtest.h"
#include "../UpParser_Polymorphisme_Lib/HelpCommand.h"


namespace COO_Parser_Classes_Tests {
    class Toto : public Command {
    public:
        Toto() : Command("TOTO", { "-toto" }, 0, "Print 'Toto Tata Titi !'", false, true) {}
        void processArgs(const std::vector<std::string>& args) {}
        void execute() {
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

    // Global variable to record the order of command execution.
    std::vector<std::string> executionOrder;

    class TestCommand : public Command {
    private:
        std::string commandName;
    public:
        TestCommand(const std::string& name) : Command(name, { "-" + name }, 1, name + " [args]", false, false), commandName(name) {}

        void processArgs(const std::vector<std::string>& args) {}

        void execute() {
            // Save the command name in the execution order.
            executionOrder.push_back(commandName);
        }
    };

    class AddCommand : public Command {
    private:
        int number1;
        int number2;
    public:
        AddCommand() : Command("Add", { "-add" }, 2, "add [args]", false, false), number1(0), number2(0) {}

        void processArgs(const std::vector<std::string>& args) {
            try {
                number1 = std::stoi(args[0]);
                number2 = std::stoi(args[1]);
            }
            catch (std::invalid_argument& e) {
                throw std::runtime_error("Les arguments doivent être des nombres valides.");
            }
        }

        void execute() {
            int sum = number1 + number2;
            std::cout << "La somme est " << sum << std::endl;
        }
    };
}

using namespace COO_Parser_Classes_Tests;

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

        // Check if an exception is thrown for the nonexistent command.
        ASSERT_THROW(parsing.parseCommandLine(argc, argv), std::invalid_argument);
    }

    // Test for executing a command and checking the return value (positive case).
    TEST(ParsingTest, ExecuteCommandeReturn) {
        Parsing parsing;

        HelloCommand hello;
        parsing.addCommand(&hello);

        char* argv[] = { "executableExecuteCommande", "-hello", "mazen", "file1"};
        int argc = sizeof(argv) / sizeof(argv[0]);


        // Capture the output of the execute function.
        std::ostringstream outputCapture;
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputCapture.rdbuf());
       
        // Call parseCommandLine to simulate the execution of the command.
        parsing.parseCommandLine(argc, argv);

        // Restore the standard output buffer.
        std::cout.rdbuf(coutBuffer);

        // Check if the output of the execute function is equal to the expected value.
        ASSERT_EQ(outputCapture.str(), "Hello, mazen!\n");
    }

    // Test for executing a command and checking for an error (negative case).
    TEST(ParsingTest, ExecuteAddCommandError) {
        Parsing parsing(true);

        AddCommand add;
        parsing.addCommand(&add);

        char* argv[] = { "executableExecuteCommande", "-add", "3", "not_a_number" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        // Call parseCommandLine to simulate the execution of the command.
        try {
            parsing.parseCommandLine(argc, argv);
           FAIL() << "Expected std::runtime_error";
        }
        catch (std::runtime_error const& err) {
            EXPECT_EQ(err.what(), std::string("Les arguments doivent être des nombres valides."));
        }
        catch (...) {
            FAIL() << "Expected std::runtime_error";
        }
    }

    // Test for the Execution Order of commands.
    TEST(ParsingTest, CommandExecutionOrder) {
        Parsing parsing;

        TestCommand command1("command1");
        TestCommand command2("command2");
        parsing.addCommand(&command1);
        parsing.addCommand(&command2);

        char* argv[] = { "executable", "-command1", "arg1", "-command2", "arg2", "file"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        // Call parseCommandLine to simulate the execution of the commands.
        parsing.parseCommandLine(argc, argv);

        // Check if the commands were executed in the correct order.
        ASSERT_EQ(executionOrder.size(), 2);
        ASSERT_EQ(executionOrder[0], "command1");
        ASSERT_EQ(executionOrder[1], "command2");
    }

}
