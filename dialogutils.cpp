#include "dialogutils.h"
#include <QMessageBox>

void DialogUtils::showAlgorithmHelp(QWidget *parent, const QString &algoName) {
    QString title = algoName + " Guide";
    QString desc = "";

    QString exampleStyle = "<div style='background-color:#f0f0f0; color:black; padding:8px; border-radius:5px; margin-top:5px;'>";

    if (algoName == "Caesar Cipher") {
        desc = "<h3>Caesar Cipher</h3>"
               "<p><b>Logic:</b> Shifts every letter by a fixed number (Key).</p>"
               "<p><b>Encryption Eq:</b> C = (P + Key) mod 26</p>"
               "<p><b>Decryption Eq:</b> P = (C - Key) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Integer (0-25).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>3</code><br><br>"
               "<b>Encrypt:</b> Input: <code>HELLO</code> -> Result: <code>KHOOR</code><br>"
               "<b>Decrypt:</b> Input: <code>KHOOR</code> -> Result: <code>HELLO</code>"
               "</div>";
    }
    else if (algoName == "Playfair Cipher") {
        desc = "<h3>Playfair Cipher</h3>"
               "<p><b>Logic:</b> Encrypts digraphs (pairs) using a 5x5 Key Matrix.</p>"
               "<p><b>Rules:</b><br>"
               "1. Same Row -> Shift Right<br>"
               "2. Same Col -> Shift Down<br>"
               "3. Rectangle -> Swap Corners</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Text Keyword (Letters only).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>MONARCHY</code><br><br>"
               "<b>Encrypt:</b> Input: <code>green</code> -> Result: <code>HEEPSR</code><br>"
               "<b>Decrypt:</b> Input: <code>HEEPSR</code> -> Result: <code>GREXEN</code>"
               "</div>";
    }
    else if (algoName == "Hill Cipher (2x2)") {
        desc = "<h3>Hill Cipher</h3>"
               "<p><b>Logic:</b> Linear Algebra (Matrix Multiplication).</p>"
               "<p><b>Encryption Eq:</b> C = (K × P) mod 26</p>"
               "<p><b>Decryption Eq:</b> P = (K⁻¹ × C) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> 4 Letters (Invertible 2x2 Matrix).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>HILL</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Short Example</code> -> Result: <code>APADJTFTWLFJ</code><br>"
               "<b>Decrypt:</b> Input: <code>APADJTFTWLFJ</code> -> Result: <code>SHORTEXAMPLE</code>"
               "</div>";
    }
    else if (algoName == "Multiplicative Cipher") {
        desc = "<h3>Multiplicative Cipher</h3>"
               "<p><b>Logic:</b> Multiplies value by key modulo 26.</p>"
               "<p><b>Encryption Eq:</b> C = (P × Key) mod 26</p>"
               "<p><b>Decryption Eq:</b> P = (C × Key⁻¹) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Integer coprime to 26 (gcd=1).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>7</code><br><br>"
               "<b>Encrypt:</b> Input: <code>HELLO</code> -> Result: <code>XCZZU</code><br>"
               "<b>Decrypt:</b> Input: <code>XCZZU</code> -> Result: <code>HELLO</code>"
               "</div>";
    }
    else if (algoName == "Affine Cipher") {
        desc = "<h3>Affine Cipher</h3>"
               "<p><b>Logic:</b> Combination of Multiplicative and Caesar.</p>"
               "<p><b>Encryption Eq:</b> C = (a × P + b) mod 26</p>"
               "<p><b>Decryption Eq:</b> P = a⁻¹ × (C - b) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Two Integers (a, b). 'a' must be coprime to 26.</p>"
               + exampleStyle +
               "<b>Example:</b> a=<code>5</code>, b=<code>8</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>Rclla</code><br>"
               "<b>Decrypt:</b> Input: <code>Rclla</code> -> Result: <code>Hello</code>"
               "</div>";
    }
    else if (algoName == "DNA Cipher") {
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
    else if (algoName == "Autokey Cipher") {
        desc = "<h3>Autokey Cipher</h3>"
               "<p><b>Logic:</b> Key is a seed letter extended by the plaintext itself.</p>"
               "<p><b>Encryption Eq:</b> Cᵢ = (Pᵢ + K_Streamᵢ) mod 26</p>"
               "<p><b>Decryption Eq:</b> Pᵢ = (Cᵢ - K_Streamᵢ) mod 26</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Single Letter (Seed).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>N</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>ULPWZ</code><br>"
               "<b>Decrypt:</b> Input: <code>ULPWZ</code> -> Result: <code>HELLO</code>"
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
    else if (algoName == "Rail Fence Cipher") {
        desc = "<h3>Rail Fence Cipher</h3>"
               "<p><b>Logic:</b> Writes text in a zigzag pattern across N rails.</p>"
               "<p><b>Operations:</b> Read row-by-row to encrypt.</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Integer > 1 (Depth).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>2</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>Hloel</code><br>"
               "<b>Decrypt:</b> Input: <code>Hloel</code> -> Result: <code>Hello</code>"
               "</div>";
    }
    else if (algoName == "Columnar Cipher") {
        desc = "<h3>Columnar Cipher</h3>"
               "<p><b>Logic:</b> Writes horizontally into a grid, reads vertically.</p>"
               "<p><b>Grid Size:</b> Rows = ⌈Len/Key⌉, Cols = Key</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Integer > 1 (Num of Columns).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>3</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Let Us Meet Today</code> -> Result: <code>L  eTaeUMtoytse d</code><br>"
               "<b>Decrypt:</b> Input: <code>L  eTaeUMtoytse d</code> -> Result: <code>Let Us Meet Today</code>"
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

    // 1. RSA Standard (مفاتيح جاهزة)
    else if (algoName == "RSA Cipher") {
        desc = "<h3>RSA Cipher (Standard)</h3>"
               "<p><b>Logic:</b> Uses pre-calculated Public/Private keys.</p>"
               "<p><b>Encryption Eq:</b> C = M^e mod n</p>"
               "<p><b>Decryption Eq:</b> M = C^d mod n</p>"
               "<hr>"
               "<p><b>How to use:</b></p>"
               "<ol>"
               "<li>Click <b>'Generate RSA Key'</b>.</li>"
               "<li>Copy the generated <b>Public Key (n, e)</b> to <b>Key a</b>.</li>"
               "<li>Type your text and click <b>Encrypt</b>.</li>"
               "<li>To Decrypt: Copy the <b>Private Key (n, d)</b> to <b>Key a</b>.</li>"
               "</ol>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Tuple format <code>(part1, part2)</code></p>"
               + exampleStyle +
               "<b>Example Scenario:</b><br>"
               "<i>Assuming the generator gave: n=3233, e=17</i><br><br>"
               "<b>Encrypt:</b> Input: <code>A</code> (65) + Key: <code>(11009, 7)</code><br>"
               "Result: <code>5875</code> (Calculated 65^17 mod 3233)<br>"
               "<b>Decrypt:</b> Input: <code>5875</code> + Key: <code>(11009, 1543)</code><br>"
               "Result: <code>A</code>"
               "</div>";
    }
    // 2. RSA Custom (حساب P و Q)
    else if (algoName == "Custom RSA Cipher") {
        desc = "<h3>Custom RSA Cipher</h3>"
               "<p><b>Logic:</b> Calculates keys (N, E, D) dynamically from Primes P and Q.</p>"
               "<p><b>Math:</b> n = p*q, phi = (p-1)*(q-1)</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Two distinct prime numbers.</p>"
               "<p>• Key a: Prime <b>P</b></p>"
               "<p>• Key b: Prime <b>Q</b></p>"
               + exampleStyle +
               "<b>Example:</b> P = <code>3</code>, Q = <code>11</code><br>"
               "<i>(System calculates n=33, e=3, d=7)</i><br><br>"
               "<b>Encrypt:</b> Input: <code>C</code> -> Result: <code>51</code><br>"
               "<b>Decrypt:</b> Input: <code>51</code> -> Result: <code>C</code>"
               "</div>";
    }

    else if (algoName == "AES Cipher") {
        desc = "<h3>AES-128 (Rijndael)</h3>"
               "<p><b>Logic:</b> Symmetric block cipher. Processes data in 128-bit blocks using substitution & permutation rounds.</p>"
               "<p><b>Process:</b> 10 Rounds of: SubBytes, ShiftRows, MixColumns, and AddRoundKey.</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Any text (internally hashed to 128-bit key).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>secret</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>4D6556CC4181997086B70D3C67EADCC9</code><br>"
               "<b>Decrypt:</b> Input: <code>4D6556CC4181997086B70D3C67EADCC9</code> -> Result: <code>Hello</code>"
               "</div>";
    }

    else if (algoName == "DES Cipher") {
        desc = "<h3>DES (Data Encryption Standard)</h3>"
               "<p><b>Logic:</b> Symmetric Feistel cipher. Older standard processing 64-bit blocks in 16 rounds.</p>"
               "<p><b>Structure:</b> Splits block into Left & Right halves. Uses Sub-keys and S-Boxes.</p>"
               "<hr>"
               "<p><b>[Key Requirement]</b> Any text (internally hashed to 56-bit effective key).</p>"
               + exampleStyle +
               "<b>Example:</b> Key = <code>secret</code><br><br>"
               "<b>Encrypt:</b> Input: <code>Hello</code> -> Result: <code>8993150E58607C62</code><br>"
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
                       "<li>Hany Mamdouh</li>"
                       "<li>Mariam Hussein</li>"
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
