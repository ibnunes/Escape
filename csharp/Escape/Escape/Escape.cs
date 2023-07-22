using System.Runtime.InteropServices;

namespace Escape;

public static class AecEscape {

    private const string EscapeFormat = "\\033[§m";
    private const char   Separator    = ';';
    
    private static readonly Dictionary<int , string> ColorMode = new() {
        { 1, "5" },
        { 3, "2"}
    };
    
    private static int CanonizeColor(int color) => color is >= 0 and <= 255 ? color : color < 0 ? 0 : 255;

    public static string Escape(params object[] args) {
        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            return "";
        
        var @catch = false;

        var color = new List<string>();
        var param = new List<string>();

        foreach (var arg in args) {
            var argType = arg.GetType();
            if (argType != typeof(string) && argType != typeof(Aec))
                continue;

            if (argType == typeof(Aec) && ((Aec)arg == Aec.Bg || (Aec)arg == Aec.Fg)) {
                if (@catch) {
                    param.Add(ColorMode[color.Count]);
                    param.AddRange(color);
                    color.Clear();
                }
                param.Add(((int)arg).ToString());
                @catch = true;
            } else {
                switch (@catch) {
                    case true when argType == typeof(int):
                        color.Add(CanonizeColor((int)arg).ToString());
                        continue;
                    case true:
                        @catch = false;
                        param.Add(ColorMode[color.Count]);
                        param.AddRange(color);
                        color.Clear();
                        break;
                }

                if (argType == typeof(Aec))
                    param.Add(((int)arg).ToString());
                else
                    param.Add((string)arg);
            }
        }

        if (color.Count > 0) {
            param.Add(ColorMode[color.Count]);
            param.AddRange(color);
        }

        var ansiCode = string.Join(Separator, param);
        return EscapeFormat.Replace("§", string.IsNullOrEmpty(ansiCode) ? "0" : ansiCode);
    }

}