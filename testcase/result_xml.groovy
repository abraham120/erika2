// This script collects all good and bad result of executed tests and writes them as xml file, using Junit formalism

// This function returns all directories in the specified path
def getDirectories(path) {
	def baseDir = new File(path)
	def filter = {file -> file.isDirectory() } as FileFilter
	return baseDir.listFiles(filter)
}

// This function searches the file specified by path parameter and returns all lines
// as elements of an array
def getLines(path) {
	def lines = []
	def f = new File( path )
	if (f.exists()) {
		f.eachLine {
			ln -> lines += [ln]
		}
	}
        return lines
}

// This class collects together the path and the result of a test
class infoElement {
	String path
	String result
}


// Searches all test related to the specified testName
def getInfoElements(String testName, def lines) {
	def result = []

	lines.each{
		def exp = testName+"/"
		if ( it =~ exp ) {
			String s = it
			def split = s.split(testName+"/")
			if (split.size() == 3) {
				result << new infoElement(path:split[2], result:split[0])
			}
		}
	}
	return result
}

// Looking for all run tests and available directories 
def allLinesTxt = []
allLinesTxt = allLinesTxt+ getLines("tmp/errors.log")
allLinesTxt = allLinesTxt+ getLines("tmp/ok.log")
def folders = getDirectories(".");
folders.sort()

// Search Jenkins environment variables
def env = System.getenv()
def base_test_name = (env.containsKey("J_arch") ? env["J_arch"]+"." : "") +
                     (env.containsKey("J_os") ? env["J_os"]+"." : "")

// Prepare the result file 
File globalResult = new File("result.xml")
globalResult.delete()
globalResult << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"+
                "<testsuites tests=\"\" failures=\"\" errors=\"\" time=\"\" name=\""+(base_test_name.size() >0? base_test_name : "tests")+"\">\n"
                
// check if each testcase directory is listed in the run test vector.
folders.each {
	String test_name = base_test_name + it.name
	String result = ""
	
	// getting all executed test.
	def lns = getInfoElements(it.name, allLinesTxt)
	lns.each{ item ->
		result += "    <testcase name=\""+item.path+"\" status=\"run\" time=\"\" classname=\""+test_name+"\">\n"

		if (item.result =~ "ERROR") {
			File log = new File(it.name+"/"+item.path+"/compile.log")
			result += "      <failure type=\"java.lang.RuntimeException\"><![CDATA["
			if (log.exists()) {
				result += log.getText()
			} else {
				result += "compile.log not found"
			}
			result += "]]></failure>\n"
			
		}
		result += "    </testcase>\n" 
	}
	result = result.size() >0 ? "<testsuite tests=\"\" failures=\"\" errors=\"\" time=\"\" name=\""+it.name+"\">\n" + result + " </testsuite>\n" : ""
	
	// append the result to result.xml file
	globalResult << result
}

// Close the result to result.xml file
globalResult << "</testsuites>\n"

