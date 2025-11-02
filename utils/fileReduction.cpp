#include <bits/stdc++.h>

/*
/ Created By Bradley Cederholm on 10/30/2025
/ Run .cpp directly with large wikipedia xml dump to reduce to a work-able <10gb file.
/ Output is only titles (sep. by \n) and the titles of the articles they link to in new lines following that.
*/

bool shouldSkip(const std::string &link)
{

    std::vector<string> skipPrefixes = {
        "File:", "Image:", "Category:", "Help:", "Template:",
        "Wikipedia:", "MediaWiki:", "User:", "Portal:", "Draft:",
        "TimedText:", "Book:", "Education Program:", "Module:",
        "Gadget:", "Gadget definition:", "Topic:", "Special:", "User talk:", "Project:", "nost:", "WP:"};

    // iterate through prefixes- remove if  needed
    for (const auto &prefix : skipPrefixes)
    {
        if (link.rfind(prefix, 0) == 0)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    // avoid weird buffer mismatches
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const std::string inputFilename = "enwiki-20251001-pages-articles-multistream.xml";
    const std::string outputFilename = "output6.txt";

    std::ifstream infile(inputFilename);
    if (!infile.is_open())
    {
        std::cerr << "Error: no input file(?)" << std::endl;
        return 0;
    }

    std::ofstream outfile(outputFilename, ios::app);
    if (!outfile.is_open())
    {
        std::cerr << "Error: no output file(?)" << std::endl;
        return 0;
    }

    std::string line;
    std::string currentTitle;
    bool inPage = false;
    size_t lineCount = 0;

    // iterate thru file to get all article pages
    while (getline(infile, line))
    {
        lineCount++;

        if (line.size() > 5'000'000)
        {
            continue;
        }

        // page start
        if (line.find("<page>") != std::string::npos)
        {
            inPage = true;
            currentTitle.clear();
            continue;
        }

        // page end
        if (line.find("</page>") != std::string::npos)
        {
            inPage = false;
            continue;
        }

        if (!inPage)
        {
            continue;
        }

        // take out title
        size_t titleStart = line.find("<title>");
        if (titleStart != string::npos)
        {
            size_t titleEnd = line.find("</title>", titleStart);
            if (titleEnd != string::npos && titleEnd > titleStart)
            {
                currentTitle = line.substr(titleStart + 7, titleEnd - (titleStart + 7));

                // i hate this why does my autoformatter do this im sobbing crying and throwing up
                outfile << "\n"
                        << currentTitle << "\n";
            }
        }

        // skip for no title
        if (currentTitle.empty())
        {
            continue;
        }

        // locates anything resembling [[#]], indicates a linked article
        size_t pos = 0;
        while ((pos = line.find("[[", pos)) != string::npos)
        {
            size_t end = line.find("]]", pos + 2);
            if (end == std::string::npos)
            {
                break;
            }

            string linkText = line.substr(pos + 2, end - (pos + 2));
            pos = end + 2;

            // some [[#]] sections include these lines(|), we can throw them out and the text before them.
            size_t linePos = linkText.find('|');
            if (linePos != std::string::npos)
            {
                linkText = linkText.substr(0, linePos);
            }

            // check if the link is actually junk- lots link to photos and files and other things that aren't articles
            if (shouldSkip(linkText))
            {
                continue;
            }

            outfile << linkText << "\n";
        }

        if (lineCount % 50000 == 0)
        {
            outfile.flush();
        }
    }

    infile.close();
    outfile.close();

    cout << "Output complete- stored in: " << outputFilename << endl;
    return 0;
}