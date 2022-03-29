#include <string>
#include <fstream>

namespace CVSTools {
    struct CVSConfiguration {
        const char* dir;
        const char* filename;
    };

    struct CVSProperties {
        std::string* headings;
        size_t col;

        ~CVSProperties()
        { delete[] headings; }
    };

    class CVS {
        CVSConfiguration config;
        std::ofstream cvsFile;

        protected:
            CVS(CVSConfiguration config);
            void WriteFile(const char* data);
    };

    class CVSHandler : protected CVS
    {
        CVSProperties* properties;
        std::string data;

         
        public:
            CVSHandler(CVSProperties* properties, CVSConfiguration config);
            ~CVSHandler();
            void CVSParser(size_t headingIndex, const char* appendData);
            void CVSParser(size_t headingIndex, char appendData);
            void CVSStart();

        private:
            void CVSHeaderParser();
            
    };
}