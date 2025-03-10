# Simple Web Server in C

This is a simple web server implemented in C that serves static files such as HTML, CSS, JavaScript, images, videos, and PDFs. The server listens on port 8080 and handles basic HTTP GET requests.

## Features

- **Static File Serving**: The server can serve static files like HTML, CSS, JavaScript, images, videos, and PDFs.
- **Basic Error Handling**: The server responds with `404 Not Found` for missing files and `405 Method Not Allowed` for unsupported HTTP methods.
- **MIME Type Detection**: The server automatically detects the MIME type of the requested file based on its extension.
- **Multi-Client Support**: The server can handle multiple client connections sequentially.

## Project Structure

- **server.c**: The main C file containing the web server implementation.
- **index.html**: The default homepage served by the server.
- **about.html**: A sample "About" page.
- **contact.html**: A sample "Contact" page.
- **404.html**: A custom 404 error page displayed when a requested file is not found.

## How to Run

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Keeththi2003/Webserver-in-C.git
   cd Webserver-in-C
   ```
2. **Complie the Server**:
    ```bash
    gcc server.c -o server
    ```

3. **Run the Server**:
    ```bash
    ./server
    ```

4. **Access the Server**:
    Open your web browser and navigate to `http://localhost:8080/`.

## Supported File Types

The server supports the following file types:

- **HTML**: `.html`
- **CSS**:`.css`
- **Javascript**: `.js`
- **Images**: `.jpg` `.jpeg` `.png`
- **Video**: `.mp4`
- **Audio**: `.mp3`
- **PDF**: `.pdf`

## Error Handling

- **404 Not Found**: If a requested file does not exist, the server responds with a custom `404.html` page.
- **405 Method Not Allowed**: If an unsupported HTTP method is used (e.g., POST), the server responds with a `405 Method Not Allowed` error.

## Customization

- **Port**: You can change the port the server listens on by modifying the PORT constant in `server.c`.

- **Error Pages**: You can customize the `404.html` page or add other error pages as needed.

- **File Types**: You can extend the `getFileType `function in `server.c` to support additional file types.


## Limitations

- This server is designed for educational purposes and is not suitable for production use.
- It does not support advanced HTTP features like caching, compression, or HTTPS.

- It handles one client at a time and does not support concurrent connections.(In the future, I will upgrade te server to support multi-threading, allowing it to handle multiple clients concurrently.)

## Contributing


Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

