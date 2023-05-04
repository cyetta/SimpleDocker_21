FROM gcc:12.1.0 as builder
WORKDIR app
RUN apt-get update && apt-get install -y libfcgi-dev && apt-get clean
RUN rm -rf /var/lib/apt/lists
COPY server/. .
RUN make

FROM nginx:1.24 as mynginx
EXPOSE 81
WORKDIR app
COPY --from=builder /app/fcgi_hello .
COPY nginx/nginx.conf /etc/nginx/nginx.conf
RUN apt-get update && apt-get install -y libfcgi-dev spawn-fcgi ; apt-get clean && rm -rf /var/lib/apt/lists/*
# append for Part 5
RUN chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    chown -R nginx:nginx /home; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid; \
    chmod u-s /usr/bin/chsh; \
    chmod u-s /usr/bin/gpasswd; \
    chmod g-s /usr/bin/wall; \
    chmod g-s /usr/bin/expiry; \
    chmod u-s /bin/mount; \
    chmod u-s /usr/bin/chfn; \
    chmod u-s /usr/bin/newgrp; \
    chmod u-s /usr/bin/passwd; \
    chmod u-s /bin/su; \
    chmod u-s /bin/umount; \
    chmod g-s /usr/bin/chage; \
    chmod g-s /sbin/unix_chkpwd
HEALTHCHECK --interval=60s --timeout=10s --retries=3 CMD curl -sS 127.0.0.1:81 || exit 1
USER nginx
CMD spawn-fcgi -p 8080 -n ./fcgi_hello & nginx -g "daemon off;"
