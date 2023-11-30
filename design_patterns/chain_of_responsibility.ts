// Logger interface
interface Logger {
    setNextLogger(logger: Logger): Logger;
    log(level: LogLevel, message: string): void;
}

// Log levels
enum LogLevel {
    Debug,
    Info,
    Warning,
    Error
}

// Base logger class
abstract class BaseLogger implements Logger {
    private nextLogger: Logger | null = null;

    setNextLogger(logger: Logger): Logger {
        this.nextLogger = logger;
        return this;
    }

    log(level: LogLevel, message: string): void {
        this.handleLog(level, message);
        if (this.nextLogger) {
            this.nextLogger.log(level, message);
        }
    }

    // Abstract method to be implemented by concrete loggers
    protected abstract handleLog(level: LogLevel, message: string): void;
}

// Concrete Logger for Debug messages
class DebugLogger extends BaseLogger {
    protected handleLog(level: LogLevel, message: string): void {
        if (level === LogLevel.Debug) {
            console.log(`[Debug] ${message}`);
        }
    }
}

// Concrete Logger for Info messages
class InfoLogger extends BaseLogger {
    protected handleLog(level: LogLevel, message: string): void {
        if (level === LogLevel.Info) {
            console.log(`[Info] ${message}`);
        }
    }
}

// Concrete Logger for Warning messages
class WarningLogger extends BaseLogger {
    protected handleLog(level: LogLevel, message: string): void {
        if (level === LogLevel.Warning) {
            console.warn(`[Warning] ${message}`);
        }
    }
}

// Concrete Logger for Error messages
class ErrorLogger extends BaseLogger {
    protected handleLog(level: LogLevel, message: string): void {
        if (level === LogLevel.Error) {
            console.error(`[Error] ${message}`);
        }
    }
}

// Client code
function useLoggingFramework(): void {
    const debugLogger = new DebugLogger();
    const infoLogger = new InfoLogger();
    const warningLogger = new WarningLogger();
    const errorLogger = new ErrorLogger();

    debugLogger.setNextLogger(infoLogger).setNextLogger(warningLogger).setNextLogger(errorLogger);

    debugLogger.log(LogLevel.Debug, 'This is a debug message');
    console.log('---');
    debugLogger.log(LogLevel.Info, 'This is an info message');
    console.log('---');
    debugLogger.log(LogLevel.Warning, 'This is a warning message');
    console.log('---');
    debugLogger.log(LogLevel.Error, 'This is an error message');
}

// Example usage
useLoggingFramework();
