#include "dialogutils.h"
#include <QMessageBox>

void DialogUtils::showAlgorithmHelp(QWidget *parent, const QString &algoName) {
    QString title = algoName + " Guide";
    QString desc = "";

    QString exampleStyle = "<div style='background-color:#f0f0f0; color:black; padding:8px; border-radius:5px; margin-top:5px;'>";

    if (algoName == "DNA Cipher") {
        desc = "<h3>DNA Cipher</h3>"
               "<p><b>Logic:</b> Binary Conversion + XOR + DNA Mapping.</p>"
               "<p><b>Steps:</b> Text->Binary XOR Key->Binary->DNA (ACGT).</p>"
               "<p><b>Map:</b> 00=A, 01=T, 10=C, 11=G</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Any Text String.</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>SECRET</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hi</code> -> Result: <code>ATCGACGA</code><br>"
               "<b>Decrypt:</b> Input: <code>ATCGACGA</code> -> Result: <code>Hi</code>"
               "</div>";
    }

    else if (algoName == "Vigenère Cipher") {
        desc = "<h3>Vigenère Cipher</h3>"
               "<p><b>Logic:</b> Polyalphabetic Shift using a keyword.</p>"
               "<p><b>Encryption Eq:</b> Cᵢ = (Pᵢ + Kᵢ) mod 26</p>"
               "<p><b>Decryption Eq:</b> Pᵢ = (Cᵢ - Kᵢ) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Keyword (Letters).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>PIZZA</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Lemon</code> -> Result: <code>Amlnn</code><br>"
               "<b>Decrypt:</b> Input: <code>Amlnn</code> -> Result: <code>Lemon</code>"
               "</div>";
    }

    else if (algoName == "Vernam Cipher") {
        desc = "<h3>Vernam Cipher</h3>"
               "<p><b>Logic:</b> One-Time Pad (XOR + Modulo Adjustment).</p>"
               "<p><b>Encryption Eq:</b> C = (P ⊕ K) mod 26</p>"
               "<p><b>Decryption Eq:</b> P = (C ⊕ K) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Text Key (Same length as msg).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>World</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>DSCWR</code><br>"
               "<b>Decrypt:</b> Input: <code>DSCWR</code> -> Result: <code>HELLO</code>"
               "</div>";
    }

    else if (algoName == "Row Transposition Cipher") {
        desc = "<h3>Row Transposition Cipher</h3>"
               "<p><b>Logic:</b> Permutes columns based on a specific numeric order.</p>"
               "<p><b>Note:</b> Adds 'X' padding to complete the grid.</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Permutation numbers (e.g., 231).</p>"
               + exampleStyle +
               "<b>Example:</b> Input: <code>TEST</code> + Key: <code>231</code><br>"
               "<i>(Padding 'XX' added -> TESTXX)</i><br><br>"
               "<b>Encrypt:</b><br>"
               "1. Read Col '1' (S, X)<br>"
               "2. Read Col '2' (T, T)<br>"
               "3. Read Col '3' (E, X)<br>"
               "Result: <code>SXTTEX</code><br><br>"
               "<b>Decrypt:</b> Input: <code>SXTTEX</code> -> Result: <code>TESTXX</code>"
               "</div>";
    }

    else if (algoName == "AES Cipher") {
        desc = "<h3>AES-128 Cipher</h3>"
               "<p><b>Logic:</b> Symmetric block cipher. Encrypts data in 128-bit blocks using 10 rounds of substitution & permutation (SPN Network).</p>"
               "<p><b>Key Processing:</b> Your key text is hashed using MD5 to create a fixed 128-bit key.</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Any text string.</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>secret</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code><br>"
               "<b>Result:</b> <code>101101001...</code> (Output is in Binary format)<br>"
               "<b>Decrypt:</b> Input: <code>101101001...</code> -> Result: <code>Hello</code>"
               "</div>";
    }

    else if (algoName == "DES Cipher") {
        desc = "<h3>DES (Data Encryption Standard)</h3>"
               "<p><b>Logic:</b> Symmetric Feistel Cipher. Encrypts 64-bit blocks using 16 rounds of substitution (S-Boxes) and permutation.</p>"
               "<p><b>Structure:</b> Initial Permutation (IP) &rarr; 16 Rounds &rarr; Final Permutation (FP).</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> 16 Hexadecimal characters (64-bit).</p>"
               "<p><i>(Recommended: Use the 'Generate Key' button to get a valid key with correct parity).</i></p>"
               + exampleStyle +
               "<b>Example:</b><br>"
               "Key: <code>1A2B3C4D5E6F7080</code> (Auto-Generated)<br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>8993150E58607C62</code> (Hex)<br>"
               "<b>Decrypt:</b> Input: <code>8993150E58607C62</code> -> Result: <code>Hello</code>"
               "</div>";
    }

    if (!desc.isEmpty()) {
        QMessageBox::about(parent, title, desc);
    }
}

void DialogUtils::showAbout(QWidget *parent) {
    QMessageBox::about(parent, "About CryptoDesk Project",
                       "<h3>CryptoDesk</h3>"
                       "<p>A comprehensive tool for learning and applying encryption algorithms.</p>"
                       "<p><b>Developed by:</b></p>"
                       "<ul>"
                       "<li>Haytham Hossam</li>"
                       "<li>Mariam Hussein</li>"
                       "<li>Hany Mamdouh</li>"
                       "<li>Omar Hany</li>"
                       "<li>Ibrahim Nour Eldeen</li>"
                       "<li>Youssef Elsayed<li>"
                       "<li>Mohamed Elsaid</li>"
                       "<li>Omar Gamal</li>"
                       "<li>Ahmed Abd-Elrahman</li>"
                       "<li>Ziad Mohamed</li>"
                       "</ul>"
                       "<p><i>© 2025 Faculty of Science, CS Department</i></p>");
}
