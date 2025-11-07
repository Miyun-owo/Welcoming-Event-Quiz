// puzzle.cpp
// Requires SFML (graphics/window/system). Compile with:
// g++ puzzle.cpp -o puzzle -lsfml-graphics -lsfml-window -lsfml-system
/*
// 記得把註解解開

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

enum Stage { STAGE1_PASSCODE, STAGE1_LOCKED, STAGE2_HACKSIM, STAGE3_TERMINAL, STAGE_DONE };

struct FakeWindow {
    sf::RectangleShape rect;
    sf::Text title;
    bool interactive = false; // installer window
    bool visible = true;
    sf::Vector2f velocity;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Mystery Terminal");
    window.setFramerateLimit(60);

    // load font (put a ttf in working dir)
    sf::Font mono;
    if (!mono.loadFromFile("DejaVuSansMono.ttf")) {
        std::cerr << "請把等寬字型 DejaVuSansMono.ttf 放在執行目錄\n";
        return 1;
    }

    // ---- UI setup ----
    Stage stage = STAGE1_PASSCODE;
    std::string passcodeInput = "";
    const std::string passcode = "731"; // 可以改成從場景/檔案來
    bool locked = false;
    sf::Clock lockClock;
    const sf::Time lockDuration = sf::seconds(60);

    // simple labels
    sf::Text title("Stage 1 - Enter 3-digit passcode", mono, 24);
    title.setPosition(20, 20);

    sf::Text prompt("Passcode: ", mono, 26);
    prompt.setPosition(20, 80);

    sf::Text info("", mono, 18);
    info.setPosition(20, 120);

    // Stage2: create many fake windows
    std::vector<FakeWindow> fws;
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::uniform_real_distribution<float> posx(0, 800), posy(100, 550), vel(-80,80);

    auto create_fake_windows = [&](int n){
        fws.clear();
        for (int i=0;i<n;i++){
            FakeWindow fw;
            fw.rect.setSize({220.f, 120.f});
            fw.rect.setFillColor(sf::Color(30 + (i*17)%200, 30 + (i*31)%200, 30 + (i*47)%200, 220));
            fw.rect.setOutlineThickness(2);
            fw.rect.setOutlineColor(sf::Color::Black);
            fw.rect.setPosition(posx(rng), posy(rng));
            fw.title.setFont(mono);
            fw.title.setCharacterSize(14);
            std::string t = (i==0? "installer_prompt" : "process_" + std::to_string(i));
            fw.title.setString(t);
            fw.title.setPosition(fw.rect.getPosition() + sf::Vector2f(6,6));
            fw.interactive = (i==0); // index 0 is the one interactive window
            fw.velocity = {vel(rng)/4.0f, vel(rng)/4.0f};
            fws.push_back(fw);
        }
    };

    // call once
    create_fake_windows(12);

    // Stage2 installer dialog state
    int installerStep = 0;
    std::vector<std::string> installerAnswers;
    std::string installerBuf = "";

    // Stage3: terminal text + virtual files
    std::vector<std::string> terminalLines;
    std::vector<std::pair<std::string,std::string>> vfiles; // name, content
    // prepare small virtual files (these are the clues)
    vfiles.push_back({"readme.txt","The color of sky is blue\n"});
    vfiles.push_back({"logs/system.log","ok m0x\ntest moon\nhelp more\n"});
    vfiles.push_back({"photo.meta","UserComment=421\n"}); // simulate EXIF

    // Terminal input buffer
    std::string termInput;

    // convenience text settings
    sf::Text passText("", mono, 28);
    passText.setPosition(160, 80);
    passText.setFillColor(sf::Color::White);

    sf::Text small("", mono, 16);
    small.setPosition(20, 160);
    small.setFillColor(sf::Color::White);

    // terminal display
    sf::Text termDisplay("", mono, 16);
    termDisplay.setPosition(20, 180);
    termDisplay.setFillColor(sf::Color::Green);

    // helper: draw centered
    auto drawCenteredString = [&](sf::RenderWindow& w, const std::string& s, int size, float y){
        sf::Text t(s, mono, size);
        sf::FloatRect r = t.getLocalBounds();
        t.setPosition((w.getSize().x - r.width)/2.0f, y);
        w.draw(t);
    };

    // main loop
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            // Text input handling depends on stage
            if (stage == STAGE1_PASSCODE) {
                if (ev.type == sf::Event::TextEntered) {
                    uint32_t c = ev.text.unicode;
                    if (c >= '0' && c <= '9' && passcodeInput.size() < 3) {
                        passcodeInput.push_back((char)c);
                    } else if (c == 8 && !passcodeInput.empty()) { // backspace
                        passcodeInput.pop_back();
                    } else if (c == '\r' || c == '\n') { // enter
                        if (passcodeInput == passcode) {
                            stage = STAGE2_HACKSIM;
                            info.setString("Passcode correct. Initializing..."); 
                            // make sure fake windows spawn
                            create_fake_windows(14);
                        } else {
                            // lock
                            stage = STAGE1_LOCKED;
                            locked = true;
                            lockClock.restart();
                            info.setString("WRONG. System locked for 60 seconds...");
                        }
                    }
                }
            } else if (stage == STAGE1_LOCKED) {
                // maybe allow ESC to quit, otherwise ignore
                if (ev.type == sf::Event::KeyPressed) {
                    if (ev.key.code == sf::Keyboard::Escape) window.close();
                }
            } else if (stage == STAGE2_HACKSIM) {
                // detect mouse click on interactive window (installer)
                if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mp(ev.mouseButton.x, ev.mouseButton.y);
                    // find top-most window under mouse (iterate reverse)
                    for (int i=(int)fws.size()-1;i>=0;i--) {
                        if (!fws[i].visible) continue;
                        if (fws[i].rect.getGlobalBounds().contains(mp)) {
                            // bring to front: move to end
                            FakeWindow fw = fws[i];
                            fws.erase(fws.begin()+i);
                            fws.push_back(fw);
                            // if interactive, set focus to installer input
                            if (fws.back().interactive) {
                                // open installer dialog (we'll use installerStep state)
                                installerStep = 1;
                                installerBuf.clear();
                                installerAnswers.clear();
                            }
                            break;
                        }
                    }
                }
                // handle text for installer dialog
                if (installerStep > 0) {
                    if (ev.type == sf::Event::TextEntered) {
                        uint32_t c = ev.text.unicode;
                        if (c == '\b' && !installerBuf.empty()) installerBuf.pop_back();
                        else if (c == '\r' || c == '\n') {
                            // submit line
                            installerAnswers.push_back(installerBuf);
                            installerBuf.clear();
                            installerStep++;
                            if (installerStep > 3) {
                                // evaluate answers (very simple)
                                bool ok = true;
                                if (installerAnswers.size() >= 3) {
                                    if (installerAnswers[0] != "y") ok = false; // accept license
                                    if (installerAnswers[1] != "3") ok = false; // choose 3
                                    if (installerAnswers[2].size() < 1) ok = false;
                                } else ok = false;
                                if (ok) {
                                    stage = STAGE3_TERMINAL;
                                    terminalLines.push_back("=== Terminal unlocked ===");
                                    terminalLines.push_back("Server asks for key parts:");
                                    terminalLines.push_back("1) color word from readme.txt");
                                    terminalLines.push_back("2) 4-letter code from logs (3rd char each line)");
                                    terminalLines.push_back("3) numeric code from photo.meta");
                                    terminalLines.push_back("Construct URL: https://treasure.example/<1>-<2>-<3>");
                                } else {
                                    // fail: close installer (player can re-open)
                                    installerStep = 0;
                                }
                            }
                        } else if (c < 128) {
                            installerBuf.push_back((char)c);
                        }
                    }
                }
            } else if (stage == STAGE3_TERMINAL) {
                // terminal reads keyboard
                if (ev.type == sf::Event::TextEntered) {
                    uint32_t c = ev.text.unicode;
                    if (c == '\b' && !termInput.empty()) termInput.pop_back();
                    else if (c == '\r' || c == '\n') {
                        // handle command
                        if (termInput == "ls") {
                            terminalLines.push_back("files:");
                            for (auto &f: vfiles) terminalLines.push_back(" - " + f.first);
                        } else if (termInput.rfind("cat ",0) == 0) {
                            std::string fname = termInput.substr(4);
                            auto it = std::find_if(vfiles.begin(), vfiles.end(), [&](auto &p){ return p.first==fname; });
                            if (it!=vfiles.end()) terminalLines.push_back(">>> " + it->second);
                            else terminalLines.push_back("No such file: " + fname);
                        } else if (termInput.rfind("solve",0) == 0) {
                            // attempt to auto-solve by reading vfiles
                            // simple solver to produce final url example: blue-MOON-421
                            std::string part1="blue";
                            // build part2 from logs third char of each line
                            std::string logs = vfiles[1].second;
                            std::string part2="";
                            std::string cur;
                            for (char ch: logs) {
                                if (ch=='\n') {
                                    if (cur.size()>=3) part2.push_back(cur[2]);
                                    cur.clear();
                                } else cur.push_back(ch);
                            }
                            std::string part3="421";
                            std::string url = "https://treasure.example/" + part1 + "-" + part2 + "-" + part3;
                            terminalLines.push_back("Constructed: " + url);
                            terminalLines.push_back("If this is correct, puzzle done.");
                        } else {
                            terminalLines.push_back("Unknown command. Try ls | cat <file> | solve");
                        }
                        termInput.clear();
                    } else if (c < 128) {
                        termInput.push_back((char)c);
                    }
                }
            }
        } // end events

        // update timers / movement
        if (stage == STAGE1_LOCKED) {
            if (lockClock.getElapsedTime() >= lockDuration) {
                // "restart" app internally
                stage = STAGE1_PASSCODE;
                passcodeInput.clear();
                info.setString("System restarted.");
            }
        }

        if (stage == STAGE2_HACKSIM) {
            // move fake windows
            for (auto &fw: fws) {
                if (!fw.visible) continue;
                sf::Vector2f pos = fw.rect.getPosition();
                pos += fw.velocity * (1.0f/60.0f);
                // bounce edges
                if (pos.x < 0 || pos.x + fw.rect.getSize().x > window.getSize().x) fw.velocity.x *= -1;
                if (pos.y < 60 || pos.y + fw.rect.getSize().y > window.getSize().y) fw.velocity.y *= -1;
                fw.rect.setPosition(pos);
                fw.title.setPosition(pos + sf::Vector2f(6,6));
                // subtle flicker: toggle visibility occasionally
                if ((std::rand()%600) == 0) fw.visible = !fw.visible;
            }
        }

        // draw
        window.clear(sf::Color(20,20,30));
        if (stage == STAGE1_PASSCODE || stage == STAGE1_LOCKED) {
            window.draw(title);
            window.draw(prompt);
            passText.setString(passcodeInput + ( (int)(std::fmod(sf::Time(clock()).asSeconds(),1.0))? "" : "_" ));
            window.draw(passText);
            window.draw(info);
            if (stage == STAGE1_LOCKED) {
                // show fullscreen fake black "locked" screen overlay with countdown
                float left = std::max(0.0f, 60.0f - lockClock.getElapsedTime().asSeconds());
                sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
                overlay.setFillColor(sf::Color(0,0,0,230));
                window.draw(overlay);
                drawCenteredString(window, "SYSTEM LOCKED", 40, 200);
                drawCenteredString(window, ("Rebooting in " + std::to_string((int)left) + "s"), 24, 260);
            }
        } else if (stage == STAGE2_HACKSIM) {
            // draw some background "desktop"
            sf::Text desk("FAKE-DESKTOP -- windows are spawning", mono, 18);
            desk.setPosition(10,10);
            window.draw(desk);
            // draw windows
            for (auto &fw: fws) {
                if (!fw.visible) continue;
                window.draw(fw.rect);
                window.draw(fw.title);
                // small jitter for random ones
                if (!fw.interactive && (std::rand()%200)==0) {
                    sf::Text x("!!", mono, 24);
                    x.setPosition(fw.rect.getPosition() + sf::Vector2f(10,40));
                    window.draw(x);
                }
            }
            // if installer open, draw its dialog content at fixed place
            if (installerStep > 0) {
                sf::RectangleShape dialog({560,200});
                dialog.setFillColor(sf::Color(10,10,10,240));
                dialog.setOutlineThickness(2);
                dialog.setOutlineColor(sf::Color::White);
                dialog.setPosition(220,220);
                window.draw(dialog);
                sf::Text dl("Installer v2.1 - interactive", mono, 20);
                dl.setPosition(230,230);
                window.draw(dl);
                sf::Text q("", mono, 18);
                q.setPosition(230,260);
                if (installerStep==1) q.setString("License? (y/n): ");
                else if (installerStep==2) q.setString("Choose package [1:logger 2:net 3:cli]: ");
                else if (installerStep==3) q.setString("Enter admin prefix (3 letters): ");
                window.draw(q);
                sf::Text ib(installerBuf + "_", mono, 18); ib.setPosition(230,300);
                window.draw(ib);
            } else {
                // instruction hint
                sf::Text hint("Find the 'installer_prompt' window (it looks slightly different) and click it.", mono, 16);
                hint.setPosition(20,40);
                window.draw(hint);
            }
        } else if (stage == STAGE3_TERMINAL) {
            // draw terminal background
            sf::RectangleShape tbg(sf::Vector2f(960,500));
            tbg.setFillColor(sf::Color(5,5,5));
            tbg.setOutlineColor(sf::Color::White);
            tbg.setOutlineThickness(2);
            tbg.setPosition(20,160);
            window.draw(tbg);
            // print terminalLines (keep last N)
            int linesToShow = 20;
            int start = std::max(0, (int)terminalLines.size()-linesToShow);
            float y = 170;
            for (int i=start;i<(int)terminalLines.size();i++){
                sf::Text t(terminalLines[i], mono, 16);
                t.setPosition(28,y);
                window.draw(t);
                y += 20;
            }
            // prompt
            sf::Text pr("> " + termInput + ( (int)(std::fmod(sf::Time(clock()).asSeconds(),1.0))? "" : "_" ), mono, 16);
            pr.setPosition(28,y+6);
            window.draw(pr);

            // small help
            sf::Text help("Try: ls | cat <file> | solve", mono, 14);
            help.setPosition(20,120);
            window.draw(help);
        }

        window.display();
    }

    return 0;
}
*/