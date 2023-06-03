#include "../headers/Menu.h"

Menu::Menu(const std::vector<std::string> &paths) {
    for (auto &path : paths)
        graphs.emplace(path, nullptr);
    headers = {"", "Backtracking", "Triangular Approximation", "Our heuristic"};
}

void Menu::readGraph(const std::string &path) {
    auto g = std::find(cachedGraphs.begin(), cachedGraphs.end(), path);
    if (g != cachedGraphs.end()) return;
    Graph *graph = new Graph();
    // TODO verificar argumentos diferentes para ler os grafos
    if (path.substr(0, path.find('/')) == "real-graphs") {
        csv::readNodes(path + "nodes.csv", graph);
        csv::readEdges(path + "edges.csv", graph);
    }
    else if (path.substr(0, path.find('/')) == "extra-graphs")
        csv::readEdges(path, graph, false, false);
    else if (path.substr(path.find_last_of('/'), path.size()) == "tourism.csv")
        csv::readEdges(path, graph, true, true);
    else csv::readEdges(path, graph);
    graphs[path] = graph;
    updateCache(path);
}

void Menu::updateCache(const std::string &path) {
    auto rm = cachedGraphs.begin();
    if (rm != cachedGraphs.end())
        graphs[*rm] = nullptr;
    if (cachedGraphs.size() > 3)
        cachedGraphs.erase(rm);
    cachedGraphs.push_back(path);
}

void Menu::init() {
    while (true) {
        cleanTerminal();
        std::cout << '|' << std::string(100, '-') << '|' << std::endl
                  << '|' <<  center("Welcome to the TSP solver!", 100) << '|' <<  std::endl
                  << '|' << center("Please select an option:", 100) << '|' << std::endl
                  << '|' << std::string(100, '-') << '|' << std::endl
                  << '|' << center("1.  Solve TSP using backtracking", 100) << '|' << std::endl
                  << '|' << center("2.  Solve TSP using triangular approximation heuristic", 100) << '|' << std::endl
                  << '|' << center("3.  Solve TSP using our heuristic", 100) << '|' << std::endl
                  << '|' << center("4.  Exit", 100) << '|' << std::endl
                  << '|' << std::string(100, '-') << '|' << std::endl
                  << std::setw(20) << std::right << "Option: ";
        std::cin >> input;
        switch (stoi(input)) {
            case 1:
                selectGraph(1);
                break;
            case 2:
                selectGraph(2);
                break;
            case 3:
                selectGraph(3);
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid option!" << std::endl;
                break;
        }
    }
}

bool Menu::selectGraph(const int headerIdx) {
    std::vector<std::string> options;
    bool alive = true;
    while (alive) {
        int i = 1;
        cleanTerminal();
        std::cout << '|' << std::string(100, '-') << '|' << std::endl
                  << '|' << center(headers[headerIdx], 100) << '|' << std::endl
                  << '|' << center("Please select a graph to solve:", 100) << '|' << std::endl
                  << '|' << std::string(100, ' ') << '|' << std::endl
                  << '|' << std::string(100, '-') << '|' << std::endl;

        for (auto &graph : graphs) {
            options.push_back(graph.first);
            std::cout << std::right << std::setw(25) << ' ' << std::to_string(i++) + "." << std::setw(3) << ' ' << graph.first << std::endl;
        }

        std:: cout << '|' << std::right << std::setw(24) << ' ' << "0.   Exit" << std::endl
                   << '|' << std::string(100, ' ') << '|' << std::endl
                   << '|' << std::string(100, '-') << '|' << std::endl
                   << std::right << std::setw(20) << "Option: ";
        std::cin >> input;
        switch (stoi(input)) {
            case 0:
                alive = false;
                break;
            default:
                readGraph(options[stoi(input) - 1]);
                alive = displayInfo(headerIdx, options[stoi(input) - 1]);
                break;
        }
    }
    return false;
}

bool Menu::displayInfo(const int headerIdx, const std::string &path) {
    std::vector<int> res;
    double elapsedTime, dist;
    switch (headerIdx) {
        case 1:
            res = measureExecutionTime(elapsedTime, *graphs[path], &Graph::tspBacktracking, dist);
            break;
        case 2:
            res = measureExecutionTime(elapsedTime, *graphs[path], &Graph::approxTSPTour, dist);
            break;
        case 3:

            break;
        default:
            return false;
    }
    bool alive = true;
    while (alive) {
        cleanTerminal();
        std::cout << '|' << std::string(100, '-') << '|' << std::endl
                  << '|' << center(headers[headerIdx] + " for " + path, 100) << '|' << std::endl
                  << '|' << std::string(100, ' ') << '|' << std::endl
                  << '|' << std::string(100, '-') << '|' << std::endl
                  << '|' << std::string(100, ' ') << '|' << std::endl
                  << '|' << center("Execution time: " + std::to_string(elapsedTime) + "ms", 100) << '|' << std::endl;
        switch (headerIdx) {
            case 1:
                std::cout << '|' << center("Best distance: " + std::to_string(dist), 100) << '|' << std::endl;
                break;
            case 2:
                std::cout << '|' << center("Distance: " + std::to_string(dist), 100) << '|' << std::endl;
                break;
            case 3:
                std::cout << '|' << center("Distance: " + std::to_string(dist), 100) << '|' << std::endl;
                break;
        }
        std::cout << '|' << std::string(100, ' ') << '|' << std::endl
                  << '|' << std::string(100, '-') << '|' << std::endl
                  << '|' << std::string(100, ' ') << '|' << std::endl
                  << '|' << center("1.  Show nodes", 100) << '|' << std::endl
                  << '|' << center("2.  Back", 100) << '|' << std::endl
                  << '|' << std::string(100, '-') << '|' << std::endl
                  << std::right << std::setw(20) << "Option: ";
        std::cin >> input;
        while (true) {
            switch (stoi(input)) {
                case 1:
                    // TODO
                    alive = true;
                    std::cout << res.size() << std::endl;
                    // displayPath(res, nodes);
                    break;
                case 2:
                    return true;
                default:
                    std::cout << "Invalid option!" << std::endl;
                    std::cin >> input;
                    break;
            }
        }
    }
    return false;
}

std::string Menu::center(const std::string &str, int width) {
    int padding = width - (int) str.size();
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    return std::string(leftPadding, ' ') + str + std::string(rightPadding, ' ');
}

void Menu::cleanTerminal() {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
