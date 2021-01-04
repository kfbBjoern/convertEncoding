#ifndef OPTIONS
#define OPTIONS

#include <string>
#include <map>
#include <variant>
#include <list>

struct OptionsInput {
    std::string LongName;
    unsigned int RequiresExtension;
    char ShortName;

    OptionsInput(std::string long_name, unsigned int requires, char short_name) :
     LongName(long_name), RequiresExtension(requires), ShortName(short_name)
     {};
};

class Options
{
    public:
        Options() = delete;
        Options(int argc, char**);
        Options(const Options& other) = delete;
        Options(Options&& other) = delete;
        Options& operator=(const Options& other) = delete;
        Options& operator=(Options&& other) = delete;
    
        ~Options()
        {
        }

        bool exists(const std::string input) const;
        std::list< std::string > getUnhandledOptions() {return UnhandledOptions;};
        std::string getExtensionFor(std::string long_name);

    private:
        std::map<std::string, std::variant<int, std::string> > AllOptions;

        std::list<OptionsInput> PossibleOptions 
        {
	    	OptionsInput(std::string("exclude"), 1u, 'E'),
		    OptionsInput(std::string("usage"),	 0u, 'U')
    	};

        std::list< std::string > UnhandledOptions;

        std::list<OptionsInput>::const_iterator equalsLongOption(const char* opt) const;
        std::list<OptionsInput>::const_iterator equalsShortOption(const char* opt) const;

};

#endif // OPTIONS