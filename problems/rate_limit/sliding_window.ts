class SlidingWindowRateLimiter {
    private requests: number[] = [];
    private windowSize: number;
    private limit: number;

    constructor(windowSize: number, limit: number) {
        this.windowSize = windowSize;
        this.limit = limit;
    }

    makeRequest(): boolean {
        const currentTime = Date.now();
        this.cleanupRequests(currentTime);

        if (this.requests.length < this.limit) {
            this.requests.push(currentTime);
            return true;
        }

        return false;
    }

    private cleanupRequests(currentTime: number): void {
        while (this.requests.length > 0 && currentTime - this.requests[0] > this.windowSize) {
            this.requests.shift();
        }
    }
}

// Example usage
const rateLimiter = new SlidingWindowRateLimiter(10000, 5); // Allow 5 requests every 10 seconds

for (let i = 0; i < 10; i++) {
    const allowed = rateLimiter.makeRequest();
    if (allowed) {
        console.log(`Request ${i + 1}: Allowed`);
    } else {
        console.log(`Request ${i + 1}: Denied`);
    }
    // Simulate time passing between requests
    setTimeout(() => {}, 1000);
}
