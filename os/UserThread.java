// UserThread - Models a users interaction with the system
//
// This class will read tasks from a file and execute the correct
// actions. It will write data to disks itself, and will start a
// PrintJobThread to perform printing.
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class UserThread extends Thread {
	// The file with the user's actions
	BufferedReader file;
	// The buffer used to process the input
	Buffer buffer;

	public UserThread(int userNumber) throws IOException {
		String filename = "USER_" + Integer.toString(userNumber);
		file = new BufferedReader(new FileReader(filename));
		buffer = new Buffer();
	}

	// readLine will read a line from the file USER_i and insert it
	// into buffer. When the end of the file has been reached, it will
	// return -1.
	private int readLine() throws IOException {
		String line;
		line = file.readLine();
		if (line == null) {
			return -1;
		}
		buffer.copyFrom(line);
		return 0;
	}


        // You must implement run. Here is a starting point, but you
        // can modify the code of run however you like. You must read
        // the file one line at a time and execute the actions
        // indicated by the file. Only use the buffer member variable
        // to process the input.
        //
        // You must write files to the Disk objects in this function,
        // and launch PrintJobThread (call start() on the
        // PrintJobThread object) to execute printing concurrently.
        //
        // When start() is called (inherited from thread) this
        // function will execute in a separate thread.
	@Override
	public void run() {
		try {
			while (readLine() != -1) {
			    // TODO: Process the input
				
				if (buffer.equals(".write")) {
					FileInfo info = new FileInfo();
					info.diskNumber = Global.diskManager.request();
					readLine();
					Buffer fileName = new Buffer();
					fileName.copyFrom(buffer);
					readLine();
					info.startingSector = Global.disks[disk].getNextFreeSector();
					info.fileLength = 0;
					while (!buffer.equals(".end")) {
						Global.disks[info.diskNumber].write(info.startingSector+info.fileLength, buffer);
						info.fileLength++;
						readLine();						
					}
					Global.diskManager.release(info.diskNumber);
					int dir = Global.directoryManager.request();
					Global.directory.insert(fileName, info);
					Global.directoryManager.release(dir);
				}
				
				else if (buffer.equals(".print")) {
					readLine();
					FileInfo info = new FileInfo();
					info = Global.directory.lookup(buffer);
					
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
